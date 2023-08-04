#pragma once

#include <string>
#include "board.h"

namespace chess {
    class Board;

    /**
     * Piece abstract class used by all pieces and space.
     */
    class Piece {
    public:

        /**
         * Piece constructor.
         * @param color the color of the piece
         * @param x_position the x coordinate on the board the piece is currently on
         * @param y_position the y coordinate on the board the piece is currently on
         * @param picture the image that is shown on cinder
         */
        Piece(int color, int x_position, int y_position, std::string picture);

        /**
         * Piece deconstructor.
         */
        virtual ~Piece();

        //https://www.tutorialspoint.com/cplusplus/cpp_interfaces.htm
        /**
         * Decides if the destination is valid move for the piece.
         * @param new_x_position the new x coordinate for the piece.
         * @param new_y_position the new y coordinate for the piece.
         * @param board the board to know surroundings of the piece
         * @return whether the move is possible
         */
        virtual bool Move(int new_x_position, int new_y_position, const Board &board) = 0;

        /**
         * Checks if the path to a certain square is valid
         * @param new_x_position the new x coordinate for the piece.
         * @param new_y_position the new y coordinate for the piece.
         * @param board the board to know surroundings of the piece
         * @return whether the path to the move is valid
         */
        virtual bool CheckPossibleMove(int new_x_position, int new_y_position, const Board &board) = 0;

        /**
         * Checks if the destination is the same color as the piece
         * @param new_x_position the new x coordinate for the piece.
         * @param new_y_position the new y coordinate for the piece.
         * @param board the board to know surroundings of the piece
         * @return true if end position is a valid destination
         */
        bool CheckSameColor(int new_x_position, int new_y_position, const Board &board) const;

        /**
         * Gets color of a piece.
         * @return the color of a piece
         */
        int get_color() const;

        /**
         * Get picture of a piece.
         * @return the picture of a piece
         */
        const std::string &get_picture() const;

        /**
         * Sets position of a piece
         * @param x the x coordinate
         * @param y the y coordinate
         */
        void SetPosition(int x, int y);

    protected:
        //0 is black piece 1 is white piece 2 is space
        int color_;
        int current_position_x_;
        int current_position_y_;
        std::string picture_;
    };
}  // namespace chess