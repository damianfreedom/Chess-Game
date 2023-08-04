#include "queen.h"

namespace chess {

    bool Queen::Move(int new_x_position, int new_y_position, const Board &board) {
        // horizontal movement
        if (current_position_x_ == new_x_position) {
            if (current_position_y_ != new_y_position) {
                return true;
            }
        }
        // vertical movement
        if (current_position_y_ == new_y_position) {
            if (current_position_x_ != new_x_position) {
                return true;
            }
        }
        //diagonal movement
        if (abs(current_position_x_ - new_x_position) == abs(current_position_y_ - new_y_position)) {
            return true;
        }
        return false;
    }

    bool Queen::CheckPossibleMove(int new_x_position, int new_y_position, const Board &board) {
        // pieces in between horizontal movement
        if (current_position_x_ == new_x_position) {
            int y_increment_rook = (new_y_position - current_position_y_) / (abs(new_y_position - current_position_y_));
            for (int col = current_position_y_ + y_increment_rook; col != new_y_position; col += y_increment_rook) {
                if (board.get_board()[new_x_position][col]->get_color() != Board::kEmptyPiece) {
                    return false;
                }
            }
            //pieces in between vertical movement
        } else if (current_position_y_ == new_y_position) {
            int x_increment_rook = (new_x_position - current_position_x_) / (abs(new_x_position - current_position_x_));
            for (int row = current_position_x_ + x_increment_rook; row != new_x_position; row += x_increment_rook) {
                if (board.get_board()[row][new_y_position]->get_color() != Board::kEmptyPiece) {
                    return false;
                }
            }
        } else if (current_position_y_ != new_y_position && current_position_x_ != new_x_position) {
            //pieces in between a diagonal movement
            int x_increment_bishop =
                    (current_position_x_ - new_x_position) / (abs(current_position_x_ - new_x_position));
            int y_increment_bishop =
                    (current_position_y_ - new_y_position) / (abs(current_position_y_ - new_y_position));

            for (int position = 1; position < abs(new_x_position - current_position_x_); position++) {
                if (board.get_board()[new_x_position + x_increment_bishop * position][new_y_position +
                                                                                      y_increment_bishop *
                                                                                      position]->get_color() !=
                    Board::kEmptyPiece) {
                    return false;
                }
            }
        }
        return true;
    }
}