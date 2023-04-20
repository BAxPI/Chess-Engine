#include <iostream>
#include "sliders_attack.h"
#include "board.h"


uint64_t mask_bishop_occupancy(int square){
    uint64_t occupancy = 0;
    
    int t_file = square % 8;
    int t_rank = square / 8;
    for(int f = t_file + 1, r = t_rank + 1; f <=6 && r<=6; f++, r++) occupancy |= (1ULL << (r * 8 + f)); 
    for(int f = t_file + 1, r = t_rank - 1; f <=6 && r>=1; f++, r--) occupancy |= (1ULL << (r * 8 + f)); 
    for(int f = t_file - 1, r = t_rank + 1; f >=1 && r<=6; f--, r++) occupancy |= (1ULL << (r * 8 + f)); 
    for(int f = t_file - 1, r = t_rank - 1; f >=1 && r>=1; f--, r--) occupancy |= (1ULL << (r * 8 + f)); 

    return occupancy;
}


uint64_t get_bishop_attack(int square, uint64_t block){
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


uint64_t mask_rook_occupancy(int square){
    uint64_t occupancy = 0;

    int t_file = square % 8;
    int t_rank = square / 8; 

    for(int f = t_file + 1; f <= 6; f++) occupancy |= (1ULL << (t_rank * 8 + f));
    for(int f = t_file - 1; f >= 1; f--) occupancy |= (1ULL << (t_rank * 8 + f));
    for(int r = t_rank + 1; r <= 6; r++) occupancy |= (1ULL << (r * 8 + t_file));
    for(int r = t_rank - 1; r >= 1; r--) occupancy |= (1ULL << (r * 8 + t_file));
    

    return occupancy;
}


uint64_t get_rook_attack(int square, uint64_t block){
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


uint64_t mask_queen_occupancy(int square){
    uint64_t occupancy = 0;

    int t_file = square % 8;
    int t_rank = square / 8; 
    // Vertical && Horizontal
    for(int f = t_file + 1; f <= 6; f++) occupancy |= (1ULL << (t_rank * 8 + f));
    for(int f = t_file - 1; f >= 1; f--) occupancy |= (1ULL << (t_rank * 8 + f));
    for(int r = t_rank + 1; r <= 6; r++) occupancy |= (1ULL << (r * 8 + t_file));
    for(int r = t_rank - 1; r >= 1; r--) occupancy |= (1ULL << (r * 8 + t_file));
    // Diagonals
    for(int f = t_file + 1, r = t_rank + 1; f <=6 && r<=6; f++, r++) occupancy |= (1ULL << (r * 8 + f)); 
    for(int f = t_file + 1, r = t_rank - 1; f <=6 && r>=1; f++, r--) occupancy |= (1ULL << (r * 8 + f)); 
    for(int f = t_file - 1, r = t_rank + 1; f >=1 && r<=6; f--, r++) occupancy |= (1ULL << (r * 8 + f)); 
    for(int f = t_file - 1, r = t_rank - 1; f >=1 && r>=1; f--, r--) occupancy |= (1ULL << (r * 8 + f)); 

    return occupancy;
}

uint64_t get_queen_attack(int square, uint64_t block){
    uint64_t attacks = 0;
    
    int t_file = square % 8;
    int t_rank = square / 8;
    // Diagonals
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

    // Horizontal && Vertical
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

uint64_t set_occupanacies(int index, int bits_in_mask, uint64_t attack_mask){
    uint64_t occupancy = 0ULL;
    for (int count = 0; count < bits_in_mask; count++){
        int square = get_lsb_index(attack_mask);
        clear_bit(attack_mask, square);
        if (index & (1 << count))
            occupancy |= (1ULL << square);
    }
    return occupancy;
}