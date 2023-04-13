#include "board.h"
#include <iostream>


void Board::print_board(uint64_t bit_board){
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
}


bool Board::get_square(int square){
    return this->bit_board & (1ULL << square);
}

void Board::set_square(squares square){
    uint64_t bit = 1ULL << square;
    bit_board |= bit;
}

void Board::clear_square(squares square){
    uint64_t bit = 1ULL << square;
    bit_board &= ~bit;
}