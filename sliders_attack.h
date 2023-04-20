#pragma once
#ifndef SLIDERS_ATTACK_H
#define SLIDERS_ATTACK_H

#include <stdint.h>
#include <array>

const std::array<int, 64> bishop_relevant_bits = {
    6, 5, 5, 5, 5, 5, 5, 6, 
    5, 5, 5, 5, 5, 5, 5, 5, 
    5, 5, 7, 7, 7, 7, 5, 5, 
    5, 5, 7, 9, 9, 7, 5, 5, 
    5, 5, 7, 9, 9, 7, 5, 5, 
    5, 5, 7, 7, 7, 7, 5, 5, 
    5, 5, 5, 5, 5, 5, 5, 5, 
    6, 5, 5, 5, 5, 5, 5, 6
};

const std::array<int, 64> rook_relevant_bits = {
    12, 11, 11, 11, 11, 11, 11, 12, 
    11, 10, 10, 10, 10, 10, 10, 11, 
    11, 10, 10, 10, 10, 10, 10, 11, 
    11, 10, 10, 10, 10, 10, 10, 11, 
    11, 10, 10, 10, 10, 10, 10, 11, 
    11, 10, 10, 10, 10, 10, 10, 11, 
    11, 10, 10, 10, 10, 10, 10, 11, 
    12, 11, 11, 11, 11, 11, 11, 12 
};
uint64_t mask_bishop_occupancy(int square);
uint64_t get_bishop_attack(int square, uint64_t block);
uint64_t mask_rook_occupancy(int square);
uint64_t get_rook_attack(int square, uint64_t block);
uint64_t mask_queen_occupancy(int square);
uint64_t get_queen_attack(int square, uint64_t block);

#endif