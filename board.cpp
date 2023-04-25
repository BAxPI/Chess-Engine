#include "board.h"
#include <iostream>
#include <array>


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
    std::cout << "Bitboard:" << bit_board << "\n\n";
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
