#include <cmath>
#include "bishop.h"

namespace chess {

    bool Bishop::Move(int new_x_position, int new_y_position, const Board &board) {
        if (abs(current_position_x_ - new_x_position) == abs(current_position_y_ - new_y_position)) {
            return true;
        }
        return false;
    }

    bool Bishop::CheckPossibleMove(int new_x_position, int new_y_position, const Board &board) {
        if (current_position_x_ == new_x_position || current_position_y_ == new_y_position) {
            return false;
        }
        int x_increment = (current_position_x_ - new_x_position) / (abs(current_position_x_ - new_x_position));
        int y_increment = (current_position_y_ - new_y_position) / (abs(current_position_y_ - new_y_position));

        //check every diagonal square to make sure it's empty
        for (int position = 1; position < abs(new_x_position - current_position_x_); position++) {
            if (board.get_board()[new_x_position + x_increment * position][new_y_position + y_increment * position]->get_color() !=
                Board::kEmptyPiece) {
                return false;
            }
        }
        return true;
    }
}