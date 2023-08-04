#include <catch2/catch.hpp>

#include <board.h>

using chess::Board;
using chess::Piece;

TEST_CASE("Valid Rook Moves") {

    Board board = Board();
    board.SetStartingPosition();

    //moving rook to middle of board so all directions of movement can be tested
    board.get_board()[7][7]->SetPosition(4, 4);
    board.get_board()[4][4]->SetPosition(7, 7);
    board.SwitchPositions(7, 7, 4, 4);

    SECTION("Horizontal movement") {

        SECTION("Left Movement") {
            REQUIRE((board.get_board()[4][4]->Move(4, 0, board) &&
                     board.get_board()[4][4]->CheckPossibleMove(4, 0, board) &&
                     board.get_board()[4][4]->CheckSameColor(4, 0, board)) == true);
        }

        SECTION("Right Movement") {
            REQUIRE((board.get_board()[4][4]->Move(4, 7, board) &&
                     board.get_board()[4][4]->CheckPossibleMove(4, 7, board) &&
                     board.get_board()[4][4]->CheckSameColor(4, 7, board)) == true);
        }
    }

    SECTION("Vertical movement") {

        SECTION("Up Movement") {
            REQUIRE((board.get_board()[4][4]->Move(2, 4, board) &&
                     board.get_board()[4][4]->CheckPossibleMove(2, 4, board) &&
                     board.get_board()[4][4]->CheckSameColor(2, 4, board)) == true);
        }

        SECTION("Down Movement") {
            REQUIRE((board.get_board()[4][4]->Move(5, 4, board) &&
                     board.get_board()[4][4]->CheckPossibleMove(5, 4, board) &&
                     board.get_board()[4][4]->CheckSameColor(5, 4, board)) == true);
        }
    }

    SECTION("Captures") {
        REQUIRE((board.get_board()[4][4]->Move(1, 4, board) &&
                 board.get_board()[4][4]->CheckPossibleMove(1, 4, board) &&
                 board.get_board()[4][4]->CheckSameColor(1, 4, board)) == true);
    }
}

TEST_CASE("Invalid Rook Movements") {

    Board board = Board();
    board.SetStartingPosition();

    //moving rook to middle of board so all directions of movement can be tested
    board.get_board()[7][7]->SetPosition(4, 4);
    board.get_board()[4][4]->SetPosition(7, 7);
    board.SwitchPositions(7, 7, 4, 4);

    SECTION("Not Straight Movement") {

        SECTION("Invalid Diagonal Movement") {
            REQUIRE((board.get_board()[4][4]->Move(5, 5, board) &&
                     board.get_board()[4][4]->CheckPossibleMove(5, 5, board) &&
                     board.get_board()[4][4]->CheckSameColor(5, 5, board)) == false);

            REQUIRE((board.get_board()[4][4]->Move(3, 3, board) &&
                     board.get_board()[4][4]->CheckPossibleMove(3, 3, board) &&
                     board.get_board()[4][4]->CheckSameColor(3, 3, board)) == false);

            REQUIRE((board.get_board()[4][4]->Move(5, 3, board) &&
                     board.get_board()[4][4]->CheckPossibleMove(5, 3, board) &&
                     board.get_board()[4][4]->CheckSameColor(5, 3, board)) == false);

            REQUIRE((board.get_board()[4][4]->Move(2, 6, board) &&
                     board.get_board()[4][4]->CheckPossibleMove(2, 6, board) &&
                     board.get_board()[4][4]->CheckSameColor(2, 6, board)) == false);
        }

        SECTION("Other random movement") {
            REQUIRE((board.get_board()[4][4]->Move(5, 7, board) &&
                     board.get_board()[4][4]->CheckPossibleMove(5, 7, board) &&
                     board.get_board()[4][4]->CheckSameColor(5, 7, board)) == false);

            REQUIRE((board.get_board()[4][4]->Move(2, 7, board) &&
                     board.get_board()[4][4]->CheckPossibleMove(2, 7, board) &&
                     board.get_board()[4][4]->CheckSameColor(2, 7, board)) == false);

            REQUIRE((board.get_board()[4][4]->Move(3, 6, board) &&
                     board.get_board()[4][4]->CheckPossibleMove(3, 6, board) &&
                     board.get_board()[4][4]->CheckSameColor(3, 6, board)) == false);
        }
    }

    SECTION("Moving Through Piece") {
        REQUIRE((board.get_board()[7][0]->Move(3, 0, board) &&
                 board.get_board()[7][0]->CheckPossibleMove(3, 0, board) &&
                 board.get_board()[7][0]->CheckSameColor(3, 0, board)) == false);

        REQUIRE((board.get_board()[7][0]->Move(7, 7, board) &&
                 board.get_board()[7][0]->CheckPossibleMove(7, 7, board) &&
                 board.get_board()[7][0]->CheckSameColor(7, 7, board)) == false);
    }

    SECTION("Same color piece capture") {
        REQUIRE((board.get_board()[7][0]->Move(6, 0, board) &&
                 board.get_board()[7][0]->CheckPossibleMove(6, 0, board) &&
                 board.get_board()[7][0]->CheckSameColor(6, 0, board)) == false);
    }
}