#pragma once
#ifndef LEAPERS_ATTACK_H
#define LEAPERS_ATTACK_H

#include <stdint.h>

enum color {white, black};
// Constants masking the A, H, GH and AB files.
const uint64_t NOT_FILE_A = 18374403900871474942UL; 
const uint64_t NOT_FILE_H = 9187201950435737471UL;
const uint64_t NOT_FILE_GH = 4557430888798830399UL;
const uint64_t NOT_FILE_AB = 18229723555195321596UL;


uint64_t get_pawn_attack(int color, int square);
uint64_t get_knight_attack(int square);
uint64_t get_king_attack_mask(int square);
#endif