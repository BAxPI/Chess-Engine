#pragma once

#include <array>
#include "board.h"

class Bitboards{
    public:
        enum Castling {WKS = 1, WQS = 2, BKS = 4, BQS = 8};
        enum Pieces {P, N, B, R, Q, K, p, n, b, r, q, k};

        /*** Constructors ***/
        Bitboards();

        /*** Methods ***/
        void print_board();
        void attacked_squares();
        bool is_square_attacked(int square, Color color);

    private:
        /*** Variables ***/ 
        std::array<uint64_t, 12> bitboards{}; 
        std::array<uint64_t, 3> occ_bitboards{}; 
        static constexpr std::string_view ascii_pieces{"PNBRQKpnbrqk"};
        int en_passant_sq = no_sq;
        int castle;
        int side = Color::White;
        std::string starting_pos{"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w - - 0 1"};

        /*** Methods ***/
        int piece_to_int(char);
        void init_occ_bitboards();
        void parse_fen_pieces(std::string); 
        void parse_fen_board_state(std::string::const_iterator& it);
};
