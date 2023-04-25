#include "board.h"
#include <iostream>
#include <array>

/****** Constructors ******/
Bitboards::Bitboards(){
    parse_fen(this->starting_pos);
}



void print_board(uint64_t bit_board){
    for (int rank = 0; rank < 8; rank++){
        for (int file = 0; file < 8; file++){
            if (file == 0){
                std::cout << 8 - rank << " ";
            }
            int square = rank * 8 + file;
            std::cout << ((bit_board & (1ULL << square)) ? " 1" : " 0");
        }
        std::cout << std::endl;
    }
    std::cout << "   a b c d e f g h" << std::endl;

    printf("\n     Bitboard: %lud\n\n", bit_board);
}


int count_bits(uint64_t bitboard){
    int counter = 0;
    while(bitboard){
        counter++;
        bitboard &= bitboard - 1;
    }
    return counter;
}


int get_lsb_index(uint64_t bitboard){
    if (!bitboard) 
        return -1;
    else 
        return count_bits((bitboard & -bitboard) -1);
}


void Bitboards::print_board(){
    for(int rank = 0; rank < 8; rank ++){
        for(int file = 0; file < 8; file++){
            if(file == 0)
                std::cout << 8 - rank << " ";
            int square = rank * 8 + file; 
            bool piece_found = false;
            for(int piece = P; piece <= k; piece++){
                if (this->bitboards[piece] & (1ULL << square)){
                    std::cout << " " << ascii_pieces[piece]; 
                    piece_found = true;
                    break;
                }
            }
            if(!piece_found){
                std::cout << " .";
            }
        }
        std::cout << std::endl;
    }
    std::cout << "   a b c d e f g h" << std::endl;
    std::cout << std::endl << std::endl;
    std::cout << "   Side: " << ((this->side == Color::White) ? "White" : "Black") << std::endl;
    std::cout << "   Enpassant: " << ((this->en_passant_sq == no_sq) ? "no" : index_to_square[this->en_passant_sq]) << std::endl;
    std::cout << "   Castling: " << ((this->castle & WKS) ? 'K': '-') << ((this->castle & WQS) ? 'Q': '-') << 
                    ((this->castle & BKS) ? 'k': '-') << ((this->castle & BQS) ? 'q': '-') << std::endl;
}


void Bitboards::parse_fen(std::string fen_string){
    /*** Setting boards && board state to empty ***/ 
    this->bitboards = {};
    this->occ_bitboards = {};
    this->side = Color::White;
    this->en_passant_sq = no_sq;
    this->castle = 0;

    /*** Parsing the pieces location ***/ 
    auto it = fen_string.begin();
    for(int rank = 0; rank < 8; rank++){
        for(int file = 0; file < 8; file++){
            int square = rank * 8 + file;
            if(isalpha(*it)){
                int bb = piece_to_int(*it);
                set_bit(this->bitboards[bb], square);
                std::advance(it, 1);
            }
            if(isdigit(*it)){
                file += (*it - '0');
                // If the square is empty fix shift
                int piece = -1;
                for(int bb_piece = Bitboards::P; bb_piece <= Bitboards::k; bb_piece++){
                    if(get_bit(bitboards[bb_piece],square)){
                        piece = bb_piece;
                    }
                }
                if(piece == -1)
                    file--;

                std::advance(it,1);
            }
            if(*it == '/'){
                std::advance(it,1);
            }
        }
    }

    /*** Parsing board state ***/
    while(isspace(*it))
        std::advance(it,1);
    this->side = (*it == 'w') ? Color::White : Color::Black; // Side to move
    std::advance(it,1);
    while(isspace(*it))
        std::advance(it,1);
    // Getting castling rights
    while(!isspace(*it)){
        switch (*it){
            case 'K':
                this->castle |= WKS; break;
                case 'Q':
                this->castle |= WQS; break;
            case 'k':
                this->castle |= BKS; break;
            case 'q':
                this->castle |= BQS; break;
            case '-': break;
        }
        std::advance(it,1); 
    }
    while(isspace(*it))
        std::advance(it,1);
    if(*it != '-'){
        int f = (*it - 'a');
        int r = 8 - ((*(it+1)) -'0');
        this->en_passant_sq = r * 8 + f;
    }

    /*** Init occupancy boards ***/ 
    for(int piece = P; piece <= K; piece++){
        this->occ_bitboards[White] |= this->bitboards[piece];
        this->occ_bitboards[Both] |= this->bitboards[piece];
    }
    for(int piece = p; piece <= k; piece++){
        this->occ_bitboards[Black] |= this->bitboards[piece];
        this->occ_bitboards[Both] |= this->bitboards[piece];
    }

}



int Bitboards::piece_to_int(char c){
    std::array<std::array<char, 2> ,12> pieces_to_int{
            {{'P', Bitboards::P}, {'N', Bitboards::N},{'B', Bitboards::B},
            {'R', Bitboards::R},{'Q', Bitboards::Q},{'K', Bitboards::K},
            {'p', Bitboards::p},{'n', Bitboards::n},{'b', Bitboards::b},
            {'r', Bitboards::r},{'q', Bitboards::q},{'k', Bitboards::k}}
        };
    for(const auto& piece: pieces_to_int){
        if(piece[0] == c)
            return piece[1];
    }    
    return -1;
}
