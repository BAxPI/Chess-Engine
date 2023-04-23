#ifndef __ATTACKS__H_
#define __ATTACKS__H_

#include <stdint.h>
#include <array>

/****** INITIALIZE ATTACKS ******/
// The engige pre-computes all possible attacks in order to be faster in-game.
// Leaping pieces: pawn, knight, king.
void init_pawn_attack();
void init_knight_attack();
void init_king_attack();

// Sliding pieces: rook, bishop.
void init_magic_numbers();
void init_sliders_attack(Sliders slider);

/****** GETTERS ******/
// Getting the pieces attack in-game.
uint64_t get_pawn_attack(Color color, int square);
uint64_t get_knight_attack(int square);
uint64_t get_king_attack(int square);
uint64_t get_bishop_attack(int square, uint64_t block);
uint64_t get_rook_attack(int square, uint64_t block);


// TESTS

#endif