#include "board.h"
#include "leapers_attack.h"


const uint64_t NOT_RANK_A = 18374403900871474942UL; 
const uint64_t NOT_RANK_H = 9187201950435737471UL;
const uint64_t not_rank_GH = 18229723555195321596UL;
const uint64_t not_rank_AB = 18229723555195321596UL;


// Precomputed attacks for each square
uint64_t pawn_attack[2][64];



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
        attack |= ((bit >> 7) & NOT_RANK_A);
        attack |= ((bit >> 9) & NOT_RANK_H);
    } else {
        attack |= (bit << 7) & NOT_RANK_H;
        attack |= (bit << 9) & NOT_RANK_A;
    }
    return attack;
}



