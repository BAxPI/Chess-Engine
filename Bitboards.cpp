#include <iostream>
#include "Bitboards.h"

/****** Constructors ******/
Bitboards::Bitboards(){
    // Setting boards && board state to empty  
    bitboards = {};
    occ_bitboards = {};
    side = Color::White;
    en_passant_sq = no_sq;
    castle = 0;

    parse_fen_pieces(starting_pos);
    init_occ_bitboards();
}


void Bitboards::print_board(){
    for(int rank = 0; rank < 8; rank ++){
        for(int file = 0; file < 8; file++){
            if(file == 0)
                std::cout << 8 - rank << " ";
            int square = rank * 8 + file; 
            bool piece_found = false;
            for(int piece = P; piece <= k; piece++){
                if (this->bitboards[piece] & (1ULL << square)){
                    std::cout << " " << ascii_pieces[piece]; 
                    piece_found = true;
                    break;
                }
            }
            if(!piece_found){
                std::cout << " .";
            }
        }
        std::cout << std::endl;
    }
    std::cout << "   a b c d e f g h" << std::endl;
    std::cout << std::endl << std::endl;
    std::cout << "   Side: " << ((side == Color::White) ? "White" : "Black") << std::endl;
    std::cout << "   Enpassant: " << ((en_passant_sq == no_sq) ? "no" : index_to_square[en_passant_sq]) << std::endl;
    std::cout << "   Castling: " << ((castle & WKS) ? 'K': '-') << ((castle & WQS) ? 'Q': '-') << 
                    ((castle & BKS) ? 'k': '-') << ((castle & BQS) ? 'q': '-') << std::endl;
}


void Bitboards::parse_fen_pieces(std::string fen_string){
    /*** Parsing the pieces location ***/ 
    std::string::const_iterator it = fen_string.begin();
    for(int rank = 0; rank < 8; rank++){
        for(int file = 0; file < 8; file++){
            int square = rank * 8 + file;
            if(isalpha(*it)){
                int bb = piece_to_int(*it);
                set_bit(this->bitboards[bb], square);
                std::advance(it, 1);
            }
            if(isdigit(*it)){
                file += (*it - '0');
                // If the square is empty fix shift
                int piece = -1;
                for(int bb_piece = Bitboards::P; bb_piece <= Bitboards::k; bb_piece++){
                    if(get_bit(bitboards[bb_piece],square)){
                        piece = bb_piece;
                    }
                }
                if(piece == -1)
                    file--;

                std::advance(it,1);
            }
            if(*it == '/'){
                std::advance(it,1);
            }
        }
    }
    parse_fen_board_state(it);

}

void Bitboards::parse_fen_board_state(std::string::const_iterator& it){

    /*** Parsing board state ***/
    while(isspace(*it))
        std::advance(it,1);
    this->side = (*it == 'w') ? Color::White : Color::Black; // Side to move
    std::advance(it,1);
    while(isspace(*it))
        std::advance(it,1);
    // Getting castling rights
    while(!isspace(*it)){
        switch (*it){
            case 'K':
                this->castle |= WKS; break;
                case 'Q':
                this->castle |= WQS; break;
            case 'k':
                this->castle |= BKS; break;
            case 'q':
                this->castle |= BQS; break;
            case '-': break;
        }
        std::advance(it,1); 
    }
    while(isspace(*it))
        std::advance(it,1);
    if(*it != '-'){
        int f = (*it - 'a');
        int r = 8 - ((*(it+1)) -'0');
        this->en_passant_sq = r * 8 + f;
    }

}

void Bitboards::init_occ_bitboards(){
    /*** Init occupancy boards ***/ 
    for(int piece = P; piece <= K; piece++){
        occ_bitboards[White] |= bitboards[piece];
        occ_bitboards[Both] |= bitboards[piece];
    }
    for(int piece = p; piece <= k; piece++){
        occ_bitboards[Black] |= bitboards[piece];
        occ_bitboards[Both] |= bitboards[piece];
    }
}


int Bitboards::piece_to_int(char c){
    std::array<std::array<char, 2> ,12> pieces_to_int{
            {{'P', Bitboards::P}, {'N', Bitboards::N},{'B', Bitboards::B},
            {'R', Bitboards::R},{'Q', Bitboards::Q},{'K', Bitboards::K},
            {'p', Bitboards::p},{'n', Bitboards::n},{'b', Bitboards::b},
            {'r', Bitboards::r},{'q', Bitboards::q},{'k', Bitboards::k}}
        };
    for(const auto& piece: pieces_to_int){
        if(piece[0] == c)
            return piece[1];
    }    
    return -1;
}

