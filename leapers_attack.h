#pragma once
#ifndef LEAPERS_ATTACK_H
#define LEAPERS_ATTACK_H

#include <stdint.h>

enum color {white, black};

uint64_t get_pawn_attack(int color, int square);

#endif