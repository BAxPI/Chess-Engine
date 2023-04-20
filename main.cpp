#include <iostream>
#include "board.h"
#include "leapers_attack.h"
#include "sliders_attack.h"


int main(int, char**) {
    uint64_t bit_board = 0ULL; 
    set_bit(bit_board, c1); 
    // print_board(bit_board);

    // print_board(mask_bishop_occupancy(e3));
    // std::cout<<count_bits((mask_bishop_occupancy(f1)))<< std::endl;

    for(int rank = 0; rank < 8; rank++){
        for (int file = 0; file < 8; file++){
            uint64_t square = rank * 8 + file;
            printf("%d, ", count_bits(mask_rook_occupancy(square)));
        }
        printf("\n");
    }


} 


