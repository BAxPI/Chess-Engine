#include "board.h"
#include "leapers_attack.h"

// Precomputed attacks for each square
uint64_t pawn_attack[2][64];
uint64_t knight_attack[64];
uint64_t king_attack[64];


void init_pawn_attack(){
   for(int i = 0; i < 64; i++){
       pawn_attack[white][i] = get_pawn_attack(white, i);
       pawn_attack[black][i] = get_pawn_attack(black, i);
   }
}


uint64_t get_pawn_attack(int color, int square){
    uint64_t attack = 0;
    uint64_t bit = 1ULL << square;
    if (color == white){
        attack |= ((bit >> 7) & NOT_FILE_A);
        attack |= ((bit >> 9) & NOT_FILE_H);
    } else {
        attack |= (bit << 7) & NOT_FILE_H;
        attack |= (bit << 9) & NOT_FILE_A;
    }
    return attack;
}


void init_knight_attack(){
   for(int i = 0; i < 64; i++){
       knight_attack[i] = get_knight_attack(i);
   }
}


uint64_t get_knight_attack(int square){
    uint64_t attack = 0UL;
    uint64_t bit = 1ULL << square;
        if ((bit >> 6) & NOT_FILE_AB) attack |= bit >> 6;
        if ((bit >> 10) & NOT_FILE_GH) attack |= bit >> 10;
        if ((bit >> 15) & NOT_FILE_A) attack |= bit >> 15;
        if ((bit >> 17) & NOT_FILE_H) attack |= bit >> 17;
        
        if ((bit << 6) & NOT_FILE_GH) attack |= bit << 6;
        if ((bit << 10) & NOT_FILE_AB) attack |= bit << 10;
        if ((bit << 15) & NOT_FILE_H) attack |= bit << 15;
        if ((bit << 17) & NOT_FILE_A) attack |= bit << 17;

    return attack;
}    


void init_king_attacl(){
    for (int i = 0; i < 64; i++){
        king_attack[i] = get_king_attack_mask(i);
    }
}

uint64_t get_king_attack_mask(int square){
    uint64_t attack = 0UL;
    uint64_t bit = 1ULL << square;
    if ((bit >> 1) & NOT_FILE_H) attack |= bit >> 1;
    if ((bit << 1) & NOT_FILE_A) attack |= bit << 1;
    if ((bit >> 7) & NOT_FILE_A) attack |= bit >> 7;
    if ((bit << 7) & NOT_FILE_H) attack |= bit << 7;
    if ((bit >> 9) & NOT_FILE_H) attack |= bit >> 9;
    if ((bit << 9) & NOT_FILE_A) attack |= bit << 9;
    attack |= bit >> 8;
    attack |= bit << 8;
    return attack;
}
















