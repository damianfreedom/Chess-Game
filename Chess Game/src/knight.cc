#include "knight.h"

namespace chess {

    bool Knight::Move(int new_x_position, int new_y_position, const Board &board) {
        if ((abs(current_position_x_ - new_x_position) == 2 && abs(current_position_y_ - new_y_position) == 1) ||
            (abs(current_position_x_ - new_x_position) == 1 && abs(current_position_y_ - new_y_position) == 2)) {
            return true;
        }
        return false;
    }

    bool Knight::CheckPossibleMove(int new_x_position, int new_y_position, const Board &board) {
        if (board.get_board()[new_x_position][new_y_position]->get_color() !=
            board.get_board()[current_position_x_][current_position_y_]->get_color()) {
            return true;
        }
        return false;
    }
}