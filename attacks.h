#ifndef __ATTACKS__H_
#define __ATTACKS__H_

#include <stdint.h>
#include <array>

/****** INITIALIZE ATTACKS ******/
// Leaping pieces: pawn, knight, king.
void init_pawn_attack();
void init_knight_attack();
void init_king_attack();

// Sliding pieces: rook, bishop.
void init_sliders_attack(Sliders slider);

/****** GETTERS ******/
uint64_t get_pawn_attack(Color color, int square);
uint64_t get_knight_attack(int square);
uint64_t get_king_attack(int square);
uint64_t get_bishop_attack(int square, uint64_t block);
uint64_t get_rook_attack(int square, uint64_t block);


// TESTS
void init_magic_number();
uint64_t get_rook_attack_on_the_fly(int square, uint64_t block);
// uint64_t mask_rook_occupancy(int square);

#endif