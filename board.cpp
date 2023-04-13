#include "board.h"
#include <iostream>


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
