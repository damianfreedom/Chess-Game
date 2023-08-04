#include "pawn.h"

namespace chess {

    bool Pawn::Move(int new_x_position, int new_y_position, const Board &board) {
        //black
        if (board.get_board()[current_position_x_][current_position_y_]->get_color() == Board::kBlackPiece) {
            // regular movement
            if (current_position_x_ == Board::kWhitePawnRow) {
                if (new_x_position - current_position_x_ <= 2 && new_y_position - current_position_y_ == 0) {
                    if (board.get_board()[current_position_x_ + 1][current_position_y_]->get_color() ==
                        Board::kEmptyPiece) {
                        return true;
                    }
                }
            } else {
                if (new_x_position - current_position_x_ == 1 && new_y_position - current_position_y_ == 0) {
                    return true;
                }
            }
            //pawn takes
            if (current_position_x_ - new_x_position == -1 && (abs(new_y_position - current_position_y_) == 1)) {
                if (board.get_board()[new_x_position][new_y_position]->get_color() == Board::kWhitePiece) {
                    return true;
                }
            }
            //white
        } else if (board.get_board()[current_position_x_][current_position_y_]->get_color() == Board::kWhitePiece) {
            // regular movement
            if (current_position_x_ == Board::kBlackPawnRow) {
                if (current_position_x_ - new_x_position <= 2 && new_y_position - current_position_y_ == 0) {
                    if (board.get_board()[current_position_x_ - 1][current_position_y_]->get_color() ==
                        Board::kEmptyPiece) {
                        return true;
                    }
                }
            } else {
                if (current_position_x_ - new_x_position == 1 && new_y_position - current_position_y_ == 0) {
                    return true;
                }
            }
            //pawn takes
            if (current_position_x_ - new_x_position == 1 && (abs(current_position_y_ - new_y_position) == 1)) {
                if (board.get_board()[new_x_position][new_y_position]->get_color() == Board::kBlackPiece) {
                    return true;
                }
            }
        }
        return false;
    }

    bool Pawn::CheckPossibleMove(int new_x_position, int new_y_position, const Board &board) {
        return true;
    }
}