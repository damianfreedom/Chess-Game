#include "piece.h"

namespace chess {

    Piece::Piece(int color, int x_position, int y_position, std::string picture) {
        color_ = color;
        current_position_x_ = x_position;
        current_position_y_ = y_position;
        picture_ = picture;
    }

    bool Piece::CheckSameColor(int new_x_position, int new_y_position, const Board &board) const {
        if (board.get_board()[new_x_position][new_y_position]->get_color() == Board::kEmptyPiece) {
            return true;
        } else if (board.get_board()[new_x_position][new_y_position]->get_color() == Board::kBlackPiece &&
                   board.get_board()[current_position_x_][current_position_y_]->get_color() == Board::kWhitePiece) {
            return true;
        } else if (board.get_board()[new_x_position][new_y_position]->get_color() == Board::kWhitePiece &&
                   board.get_board()[current_position_x_][current_position_y_]->get_color() == Board::kBlackPiece) {
            return true;
        }
        return false;
    }

    int Piece::get_color() const {
        return color_;
    }

    const std::string &Piece::get_picture() const {
        return picture_;
    }

    void Piece::SetPosition(int x, int y) {
        current_position_x_ = x;
        current_position_y_ = y;
    }

    Piece::~Piece() = default;

}
