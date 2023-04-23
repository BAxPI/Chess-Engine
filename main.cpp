#include <iostream>
#include "board.h"
#include "attacks.h"
#include <unistd.h>
void init_all(){
    init_pawn_attack();
    init_knight_attack();
    init_king_attack();

    // Sliding pieces: rook, bishop.
    init_magic_numbers();
    // get_magic_numbers();
    init_sliders_attack(Sliders::rook);
    init_sliders_attack(Sliders::bishop);
}


int main(int, char**) {
    std::cout << "Initiating..." << std::endl;
    init_all();
    std::cout << "Initiation completed." << std::endl;
    uint64_t bit_board = 0ULL; 
    set_bit(bit_board, e7); 
    set_bit(bit_board, e3); 
    set_bit(bit_board, b5); 
    set_bit(bit_board, f5); 
    set_bit(bit_board, f6); 
    set_bit(bit_board, c7); 
    set_bit(bit_board, b2); 
    set_bit(bit_board, f4); 
    print_board(bit_board);

    print_board(get_rook_attack(h8, bit_board));
    print_board(get_bishop_attack(a1, bit_board));   
} 


