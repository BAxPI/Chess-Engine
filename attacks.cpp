#include <iostream>
#include "board.h"
#include "xorshift_random.h" //XOR32SHIFT Algorithm to create a pseudo random number
#include <istream>
#include <fstream>

/****** LEAPING PIECES ATTACKS ******/

// Leaping pieces precomputed attacks (pawn, knight, king)
static std::array<std::array<uint64_t, 64>, 2> pawn_attack; 
static std::array<uint64_t, 64> knight_attack;
static std::array<uint64_t, 64> king_attack;


static uint64_t get_pawn_attack_mask(Color color, int square){
    uint64_t attack = 0;
    uint64_t bit = 1ULL << square;
    if (color == Color::White){
        attack |= ((bit >> 7) & NOT_FILE_A);
        attack |= ((bit >> 9) & NOT_FILE_H);
    } else {
        attack |= (bit << 7) & NOT_FILE_H;
        attack |= (bit << 9) & NOT_FILE_A;
    }
    return attack;
}


void init_pawn_attack(){
   for(int i = 0; i < 64; i++){
       pawn_attack[Color::White][i] = get_pawn_attack_mask(Color::White, i);
       pawn_attack[Color::Black][i] = get_pawn_attack_mask(Color::Black, i);
   }
}


uint64_t get_pawn_attack(Color color, int square){
    return pawn_attack[color][square];
}


static uint64_t get_knight_attack_mask(int square){
    uint64_t attack = 0UL;
    uint64_t bit = 1ULL << square;
        if ((bit >> 6) & NOT_FILE_AB) attack |= bit >> 6;
        if ((bit >> 10) & NOT_FILE_GH) attack |= bit >> 10;
        if ((bit >> 15) & NOT_FILE_A) attack |= bit >> 15;
        if ((bit >> 17) & NOT_FILE_H) attack |= bit >> 17;
        
        if ((bit << 6) & NOT_FILE_GH) attack |= bit << 6;
        if ((bit << 10) & NOT_FILE_AB) attack |= bit << 10;
        if ((bit << 15) & NOT_FILE_H) attack |= bit << 15;
        if ((bit << 17) & NOT_FILE_A) attack |= bit << 17;

    return attack;
}    


void init_knight_attack(){
   for(int i = 0; i < 64; i++){
       knight_attack[i] = get_knight_attack_mask(i);
   }
}


uint64_t get_knight_attack(int square){
    return knight_attack[square];
}


static uint64_t get_king_attack_mask(int square){
    uint64_t attack = 0UL;
    uint64_t bit = 1ULL << square;
    if ((bit >> 1) & NOT_FILE_H) attack |= bit >> 1;
    if ((bit << 1) & NOT_FILE_A) attack |= bit << 1;
    if ((bit >> 7) & NOT_FILE_A) attack |= bit >> 7;
    if ((bit << 7) & NOT_FILE_H) attack |= bit << 7;
    if ((bit >> 9) & NOT_FILE_H) attack |= bit >> 9;
    if ((bit << 9) & NOT_FILE_A) attack |= bit << 9;
    attack |= bit >> 8;
    attack |= bit << 8;
    return attack;
}


void init_king_attack(){
    for (int i = 0; i < 64; i++){
        king_attack[i] = get_king_attack_mask(i);
    }
}


uint64_t get_king_attack(int square){
    return king_attack[square];
}


/****** SLIDING PIECES ATTACKS ******/

// Sliding pieces precomputed attack, for every possible occupancy.
static std::array<std::array<uint64_t, 512> ,64>bishop_attacks;
static std::array<std::array<uint64_t, 4096> ,64>rook_attacks;

// Magic numbers to get fast access to the sliding pieces attacks
std::array<uint64_t,64> bishop_magic_numbers;
std::array<uint64_t,64> rook_magic_numbers;

// Sliding pieces attack masks
std::array<uint64_t, 64>bishop_masks;
std::array<uint64_t, 64> rook_masks;


// Mapping the number of relevant bits in an occupancy board of bishop attack from each square.
const std::array<int, 64> bishop_relevant_bits = {
    6, 5, 5, 5, 5, 5, 5, 6, 
    5, 5, 5, 5, 5, 5, 5, 5, 
    5, 5, 7, 7, 7, 7, 5, 5, 
    5, 5, 7, 9, 9, 7, 5, 5, 
    5, 5, 7, 9, 9, 7, 5, 5, 
    5, 5, 7, 7, 7, 7, 5, 5, 
    5, 5, 5, 5, 5, 5, 5, 5, 
    6, 5, 5, 5, 5, 5, 5, 6
};

// Mapping the number of relevant bits in an occupancy board of rook attack from each square.
const std::array<int, 64> rook_relevant_bits = {
    12, 11, 11, 11, 11, 11, 11, 12, 
    11, 10, 10, 10, 10, 10, 10, 11, 
    11, 10, 10, 10, 10, 10, 10, 11, 
    11, 10, 10, 10, 10, 10, 10, 11, 
    11, 10, 10, 10, 10, 10, 10, 11, 
    11, 10, 10, 10, 10, 10, 10, 11, 
    11, 10, 10, 10, 10, 10, 10, 11, 
    12, 11, 11, 11, 11, 11, 11, 12 
};


static uint64_t mask_bishop_occupancy(int square){
    uint64_t occupancy = 0;

    int t_file = square % 8;
    int t_rank = square / 8;

    for(int f = t_file + 1, r = t_rank + 1; f <=6 && r<=6; f++, r++) occupancy |= (1ULL << (r * 8 + f)); 
    for(int f = t_file + 1, r = t_rank - 1; f <=6 && r>=1; f++, r--) occupancy |= (1ULL << (r * 8 + f)); 
    for(int f = t_file - 1, r = t_rank + 1; f >=1 && r<=6; f--, r++) occupancy |= (1ULL << (r * 8 + f)); 
    for(int f = t_file - 1, r = t_rank - 1; f >=1 && r>=1; f--, r--) occupancy |= (1ULL << (r * 8 + f)); 

    return occupancy;
}


static uint64_t get_bishop_attack_on_the_fly(int square, uint64_t block){
    uint64_t attacks = 0;

    int t_file = square % 8;
    int t_rank = square / 8;

    for(int f = t_file + 1, r = t_rank + 1; f <=7 && r<=7; f++, r++){
        attacks |= (1ULL << (r * 8 + f));  
        if(((1ULL << (r * 8 + f)) & block)){
            break;
        }
    } 
    for(int f = t_file + 1, r = t_rank - 1; f <=7 && r>=0; f++, r--){
        attacks |= (1ULL << (r * 8 + f));  
        if(((1ULL << (r * 8 + f)) & block)){
            break;
        }
    }
    for(int f = t_file - 1, r = t_rank + 1; f >=0 && r<=7; f--, r++){
        attacks |= (1ULL << (r * 8 + f));  
        if(((1ULL << (r * 8 + f)) & block)){
            break;
        }
    } 
    for(int f = t_file - 1, r = t_rank - 1; f >=0 && r>=0; f--, r--){
        attacks |= (1ULL << (r * 8 + f));  
        if(((1ULL << (r * 8 + f)) & block)){
            break;
        }
    } 
    return attacks;
}


static uint64_t mask_rook_occupancy(int square){
    uint64_t occupancy = 0;

    int t_file = square % 8;
    int t_rank = square / 8; 

    for(int f = t_file + 1; f <= 6; f++) occupancy |= (1ULL << (t_rank * 8 + f));
    for(int f = t_file - 1; f >= 1; f--) occupancy |= (1ULL << (t_rank * 8 + f));
    for(int r = t_rank + 1; r <= 6; r++) occupancy |= (1ULL << (r * 8 + t_file));
    for(int r = t_rank - 1; r >= 1; r--) occupancy |= (1ULL << (r * 8 + t_file));
    
    return occupancy;
}


static uint64_t get_rook_attack_on_the_fly(int square, uint64_t block){
    uint64_t attacks = 0;
    
    int t_file = square % 8;
    int t_rank = square / 8;
    for(int f = t_file + 1; f <=7; f++){
        attacks |= (1ULL << (t_rank * 8 + f));  
        if(((1ULL << (t_rank * 8 + f)) & block)){
            break;
        }
    } 
    for(int f = t_file - 1; f >= 0 ; f--){
        attacks |= (1ULL << (t_rank * 8 + f));  
        if(((1ULL << (t_rank * 8 + f)) & block)){
            break;
        }
    }
    for(int r = t_rank + 1; r<=7;r++){
        attacks |= (1ULL << (r * 8 + t_file));  
        if(((1ULL << (r * 8 + t_file)) & block)){
            break;
        }
    } 
    for(int r = t_rank - 1; r>=0;r--){
        attacks |= (1ULL << (r * 8 + t_file));  
        if(((1ULL << (r * 8 + t_file)) & block)){
            break;
        }
    }
    return attacks;
}


static uint64_t set_occupanacies(int index, int bits_in_mask, uint64_t attack_mask){
    uint64_t occupancy = 0ULL;
    for (int count = 0; count < bits_in_mask; count++){
        int square = get_lsb_index(attack_mask);
        clear_bit(attack_mask, square);
        if (index & (1 << count))
            occupancy |= (1ULL << square);
    }
    return occupancy;
}


uint64_t generate_magic_number(){
    return get_random_U64_number() & get_random_U64_number() & get_random_U64_number();
}


uint64_t find_magic_number(int square, int relevant_bits, Sliders slider){
    std::array<uint64_t, 4096> occupancies;
    std::array<uint64_t, 4096> attacks;
    std::array<uint64_t, 4096> used_attacks;
    uint64_t attack_mask = (slider == Sliders::bishop) ? mask_bishop_occupancy(square) : mask_rook_occupancy(square);    

    int occupancy_indices = 1 << relevant_bits;

    for(int index = 0; index < occupancy_indices; index ++){
        occupancies[index] = set_occupanacies(index, relevant_bits, attack_mask);
        attacks[index] = (slider == Sliders::bishop) ? get_bishop_attack_on_the_fly(square, occupancies[index]) : get_rook_attack_on_the_fly(square, occupancies[index]);
    }

    // Test magic numbers
    for(int random_count = 0; random_count < 100000000; random_count++){
        uint64_t magic_number = generate_magic_number();
        if(count_bits((attack_mask * magic_number) & 0xFF00000000000000) < 6) continue;

        used_attacks = {};
        int index, fail;

        for(index = 0, fail = 0; !fail && index < occupancy_indices; index++){
            int magic_index = (int)((occupancies[index] * magic_number) >> (64 - relevant_bits));

            if(used_attacks[magic_index] == 0ULL)
                used_attacks[magic_index] = attacks[index];
            else if(used_attacks[magic_index] != attacks[index])
                fail = 1;
        }
        if (!fail)
            return magic_number;
    }
    std::cout << "Magic number failed!" << std::endl;
    return 0ULL;
}


void get_magic_numbers(){
    std::ofstream file("../magic_numbers.txt"); 
    for(int square = 0; square < 64; square++){
        rook_magic_numbers[square] = find_magic_number(square, rook_relevant_bits[square], Sliders::rook);
        file << rook_magic_numbers[square] << std::endl;
    }
    for(int square = 0; square < 64; square++){
        bishop_magic_numbers[square] = find_magic_number(square, bishop_relevant_bits[square], Sliders::bishop);
        file << bishop_magic_numbers[square] << std::endl;
    }
}


void init_magic_numbers(){
    std::ifstream file("../magic_numbers.txt");
    if (!file.is_open()) {
        get_magic_numbers();
        return;
    }
    std::string line;
    for(int i=0; i<64; i++){
        if(std::getline(file, line)) {
            bishop_magic_numbers[i] = std::stoull(line);
            std::cout<<std::hex<<bishop_magic_numbers[i] << std::endl;
        }
    }
    for(int i=0; i<64; i++){
        if (std::getline(file, line)) {
            rook_magic_numbers[i] = std::stoull(line);
            std::cout<<std::hex<<rook_magic_numbers[i] << std::endl;
        }
    }
    
    file.close();
}


void init_sliders_attack(Sliders slider){
    for(int square = 0; square < 64; square++){
        bishop_masks[square] = mask_bishop_occupancy(square);
        rook_masks[square] = mask_rook_occupancy(square);

        uint64_t attack_mask = (slider == Sliders::bishop) ? bishop_masks[square]  : rook_masks[square];


        int relevant_bits = count_bits(attack_mask);

        uint64_t occupancy_indices = (1 << relevant_bits);

        for(int index = 0; index < occupancy_indices; index++){
            // Rook    
            if(slider == Sliders::rook){
                uint64_t occupancy = set_occupanacies(index, relevant_bits, attack_mask);
                int magic_index = (occupancy * rook_magic_numbers[square]) >> (64 - rook_relevant_bits[square]);
                rook_attacks[square][magic_index] = get_rook_attack_on_the_fly(square, occupancy);
            }        
            // Bishop
            else if(slider == Sliders::bishop){
                uint64_t occupancy = set_occupanacies(index, relevant_bits, attack_mask);
                int magic_index = (occupancy * bishop_magic_numbers[square]) >> (64 - bishop_relevant_bits[square]);
                bishop_attacks[square][magic_index] = get_bishop_attack_on_the_fly(square, occupancy);
            }

        }        
    }
}


uint64_t get_bishop_attack(int square, uint64_t block){
    block &= bishop_masks[square];
    block *= bishop_magic_numbers[square];
    block >>= 64 - bishop_relevant_bits[square];

    return bishop_attacks[square][block];
}


uint64_t get_rook_attack(int square, uint64_t block){
    block &= rook_masks[square];
    block *= rook_magic_numbers[square];
    block >>= 64 - rook_relevant_bits[square];

    return rook_attacks[square][block];
}

