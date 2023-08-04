#include <catch2/catch.hpp>

#include <board.h>

using chess::Board;
using chess::Piece;

TEST_CASE("Valid Queen Moves") {

    Board board = Board();
    board.SetStartingPosition();

    //moving queen to middle of board so all directions of movement can be tested
    board.get_board()[7][3]->SetPosition(4, 4);
    board.get_board()[4][4]->SetPosition(7, 3);
    board.SwitchPositions(7, 3, 4, 4);

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

    SECTION("Diagonal Movements") {

        SECTION("Up and Right") {
            REQUIRE((board.get_board()[4][4]->Move(2, 6, board) &&
                     board.get_board()[4][4]->CheckPossibleMove(2, 6, board) &&
                     board.get_board()[4][4]->CheckSameColor(2, 6, board)) == true);
        }

        SECTION("Up and Left") {
            REQUIRE((board.get_board()[4][4]->Move(2, 2, board) &&
                     board.get_board()[4][4]->CheckPossibleMove(2, 2, board) &&
                     board.get_board()[4][4]->CheckSameColor(2, 2, board)) == true);
        }

        SECTION("Down and Right") {
            REQUIRE((board.get_board()[4][4]->Move(5, 3, board) &&
                     board.get_board()[4][4]->CheckPossibleMove(5, 3, board) &&
                     board.get_board()[4][4]->CheckSameColor(5, 3, board)) == true);
        }

        SECTION("Down and Left") {
            REQUIRE((board.get_board()[4][4]->Move(5, 5, board) &&
                     board.get_board()[4][4]->CheckPossibleMove(5, 5, board) &&
                     board.get_board()[4][4]->CheckSameColor(5, 5, board)) == true);
        }
    }

    SECTION("Captures") {
        REQUIRE((board.get_board()[4][4]->Move(1, 4, board) &&
                 board.get_board()[4][4]->CheckPossibleMove(1, 4, board) &&
                 board.get_board()[4][4]->CheckSameColor(1, 4, board)) == true);

        REQUIRE((board.get_board()[4][4]->Move(1, 1, board) &&
                 board.get_board()[4][4]->CheckPossibleMove(1, 1, board) &&
                 board.get_board()[4][4]->CheckSameColor(1, 1, board)) == true);

        REQUIRE((board.get_board()[4][4]->Move(1, 7, board) &&
                 board.get_board()[4][4]->CheckPossibleMove(1, 7, board) &&
                 board.get_board()[4][4]->CheckSameColor(1, 7, board)) == true);
    }
}

TEST_CASE("Invalid Queen Moves") {

    Board board = Board();
    board.SetStartingPosition();

    SECTION("Move through piece") {
        REQUIRE((board.get_board()[7][3]->Move(7, 5, board) &&
                 board.get_board()[7][3]->CheckPossibleMove(7, 5, board) &&
                 board.get_board()[7][3]->CheckSameColor(7, 5, board)) == false);
    }

    //moving queen to middle of board so all directions of movement can be tested
    board.get_board()[7][3]->SetPosition(4, 4);
    board.get_board()[4][4]->SetPosition(7, 3);
    board.SwitchPositions(7, 3, 4, 4);

    SECTION("Not diagonal, horizontal, or vertical movement") {
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

    SECTION("Same color capture") {
        REQUIRE((board.get_board()[4][4]->Move(6, 4, board) &&
                 board.get_board()[4][4]->CheckPossibleMove(6, 4, board) &&
                 board.get_board()[4][4]->CheckSameColor(6, 4, board)) == false);
    }
}

