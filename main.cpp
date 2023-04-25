#include <iostream>
#include "board.h"
#include "Bitboards.h"
#include "attacks.h"
#include <unistd.h>

void init_all(){
    init_pawn_attack();
    init_knight_attack();
    init_king_attack();

    // Sliding pieces: rook, bishop.
    init_magic_numbers();
    init_sliders_attack(Sliders::rook);
    init_sliders_attack(Sliders::bishop);
}


int main(int, char**) {
    std::cout << "Initiating..." << std::endl;
    init_all();
    std::cout << "Initiation completed." << std::endl;

    Bitboards bb;
    bb.print_board(); 
    return 0;
} 


