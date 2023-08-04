#pragma once

#include "piece.h"
#include "board.h"

namespace chess {

    /**
     * Class for the Rook piece and it's movements
     */
    class Rook : public Piece {
    public:
        /**
         * Rook constructor.
         * @param color the color of the piece
         * @param x_position the x coordinate on the board the piece is currently on
         * @param y_position the y coordinate on the board the piece is currently on
         * @param picture the image that is shown on cinder
         */
        Rook(int color, int x_position, int y_position, std::string picture) : Piece(color, x_position, y_position,
                                                                                     picture) {}

        /**
         * Decides if the destination is valid move for the piece.
         * @param new_x_position the new x coordinate for the piece.
         * @param new_y_position the new y coordinate for the piece.
         * @param board the board to know surroundings of the piece
         * @return whether the move is possible
         */
        bool Move(int new_x_position, int new_y_position, const Board &board) override;

        /**
         * Checks if the path to a certain square is valid
         * @param new_x_position the new x coordinate for the piece.
         * @param new_y_position the new y coordinate for the piece.
         * @param board the board to know surroundings of the piece
         * @return whether the path to the move is valid
         */
        bool CheckPossibleMove(int new_x_position, int new_y_position, const Board &board) override;
    };
}  // namespace chess
