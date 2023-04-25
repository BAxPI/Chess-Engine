#ifndef __BOARD__H_
#define __BOARD__H_

#include <stdint.h>
#include <array>
#include <string_view>
#include <string>


enum Color{White, Black, Both};
enum Sliders {rook, bishop};

/* Bit manipulations */
#define get_bit(bit_board, square) ((bit_board) & (1ULL << (square)))
#define set_bit(bit_board, square) ((bit_board) |= (1ULL << (square)))
#define clear_bit(bit_board, square) ((bit_board) &= ~(1ULL << (square)))
int count_bits(uint64_t bitboard);
int get_lsb_index(uint64_t bitboard);


enum squares {
    a8 = 0, b8, c8, d8, e8, f8, g8, h8,
    a7, b7, c7, d7, e7, f7, g7, h7,
    a6, b6, c6, d6, e6, f6, g6, h6,
    a5, b5, c5, d5, e5, f5, g5, h5,
    a4, b4, c4, d4, e4, f4, g4, h4,
    a3, b3, c3, d3, e3, f3, g3, h3,
    a2, b2, c2, d2, e2, f2, g2, h2,
    a1, b1, c1, d1, e1, f1, g1, h1, no_sq = -1
};

constexpr std::array<std::string_view, 64> index_to_square = {
    "a8" , "b8", "c8", "d8", "e8", "f8", "g8", "h8",
    "a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7",
    "a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6",
    "a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5",
    "a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4",
    "a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3",
    "a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2",
    "a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1"
};

class Bitboards{
    public:
        enum Castling {WKS = 1, WQS = 2, BKS = 4, BQS = 8};
        enum Pieces {P, N, B, R, Q, K, p, n, b, r, q, k};
        
        static constexpr std::string_view ascii_pieces{"PNBRQKpnbrqk"};
        std::array<uint64_t, 12> bitboards{}; // Need to move to private after having the functions to handle bits
        std::array<uint64_t, 3> occ_bitboards{}; // TODO: move to private
        int en_passant_sq = no_sq;
        int castle;
        int side = Color::White;

        Bitboards();
        void print_board();
    private:
        std::string starting_pos{"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w - - 0 1"};
        int piece_to_int(char);
        void parse_fen(std::string); 
};

// Constants masking the A, H, GH and AB files.
constexpr uint64_t NOT_FILE_A = 18374403900871474942UL; 
constexpr uint64_t NOT_FILE_H = 9187201950435737471UL;
constexpr uint64_t NOT_FILE_GH = 4557430888798830399UL;
constexpr uint64_t NOT_FILE_AB = 18229723555195321596UL;


void print_board(uint64_t bit_board);

#endif