#include <catch2/catch.hpp>

#include <board.h>

using chess::Board;
using chess::Piece;

TEST_CASE("Valid Bishop Moves") {

    Board board = Board();
    board.SetStartingPosition();

    //moving pawns up to allow for bishop movement
    board.get_board()[6][3]->SetPosition(5, 3);
    board.get_board()[5][3]->SetPosition(6, 3);
    board.SwitchPositions(6, 3, 5, 3);

    board.get_board()[6][1]->SetPosition(5, 1);
    board.get_board()[5][1]->SetPosition(6, 1);
    board.SwitchPositions(6, 1, 5, 1);

    board.get_board()[1][3]->SetPosition(2, 3);
    board.get_board()[2][3]->SetPosition(1, 3);
    board.SwitchPositions(1, 3, 2, 3);

    board.get_board()[1][1]->SetPosition(2, 1);
    board.get_board()[2][1]->SetPosition(1, 1);
    board.SwitchPositions(1, 1, 2, 1);

    SECTION("Valid Diagonal Movement") {

        SECTION("Up and Left") {
            REQUIRE((board.get_board()[7][2]->Move(5, 0, board) &&
                     board.get_board()[7][2]->CheckPossibleMove(5, 0, board) &&
                     board.get_board()[7][2]->CheckSameColor(5, 0, board)) == true);
        }

        SECTION("Up and Right") {
            REQUIRE((board.get_board()[7][2]->Move(4, 5, board) &&
                     board.get_board()[7][2]->CheckPossibleMove(4, 5, board) &&
                     board.get_board()[7][2]->CheckSameColor(4, 5, board)) == true);
        }

        SECTION("Down and Left") {
            REQUIRE((board.get_board()[0][2]->Move(2, 0, board) &&
                     board.get_board()[0][2]->CheckPossibleMove(2, 0, board) &&
                     board.get_board()[0][2]->CheckSameColor(2, 0, board)) == true);
        }

        SECTION("Down and Right") {
            REQUIRE((board.get_board()[0][2]->Move(3, 5, board) &&
                     board.get_board()[0][2]->CheckPossibleMove(3, 5, board) &&
                     board.get_board()[0][2]->CheckSameColor(3, 5, board)) == true);
        }
    }

    SECTION("Captures") {
        //moving pawn in scope of bishop
        board.get_board()[1][7]->SetPosition(2, 7);
        board.get_board()[2][7]->SetPosition(1, 7);
        board.SwitchPositions(1, 7, 2, 2);

        REQUIRE((board.get_board()[7][2]->Move(2, 7, board) &&
                board.get_board()[7][2]->CheckPossibleMove(2, 7, board) &&
                board.get_board()[7][2]->CheckSameColor(2, 7, board)) == true);
    }
}

TEST_CASE("Invalid Bishop Moves") {

    Board board = Board();
    board.SetStartingPosition();

    //moving pawns up to allow for bishop movement
    board.get_board()[6][3]->SetPosition(5, 3);
    board.get_board()[5][3]->SetPosition(6, 3);
    board.SwitchPositions(6, 3, 5, 3);

    board.get_board()[6][1]->SetPosition(5, 1);
    board.get_board()[5][1]->SetPosition(6, 1);
    board.SwitchPositions(6, 1, 5, 1);

    board.get_board()[1][3]->SetPosition(2, 3);
    board.get_board()[2][3]->SetPosition(1, 3);
    board.SwitchPositions(1, 3, 2, 3);

    board.get_board()[1][1]->SetPosition(2, 1);
    board.get_board()[2][1]->SetPosition(1, 1);
    board.SwitchPositions(1, 1, 2, 1);

    SECTION("Moving through other piece") {
        REQUIRE((board.get_board()[7][5]->Move(4, 2, board) &&
                 board.get_board()[7][5]->CheckPossibleMove(4, 2, board) &&
                 board.get_board()[7][5]->CheckSameColor(4, 2, board)) == false);

        REQUIRE((board.get_board()[0][5]->Move(5, 0, board) &&
                 board.get_board()[0][5]->CheckPossibleMove(5, 0, board) &&
                 board.get_board()[0][5]->CheckSameColor(5, 0, board)) == false);
    }

    SECTION("Moving up") {
        REQUIRE((board.get_board()[7][5]->Move(7, 3, board) &&
                 board.get_board()[7][5]->CheckPossibleMove(7, 3, board) &&
                 board.get_board()[7][5]->CheckSameColor(7, 3, board)) == false);

        REQUIRE((board.get_board()[7][5]->Move(7, 4, board) &&
                 board.get_board()[7][5]->CheckPossibleMove(7, 4, board) &&
                 board.get_board()[7][5]->CheckSameColor(7, 4, board)) == false);
    }

    SECTION("Taking piece of same color") {
        REQUIRE((board.get_board()[7][5]->Move(6, 4, board) &&
                 board.get_board()[7][5]->CheckPossibleMove(6, 4, board) &&
                 board.get_board()[7][5]->CheckSameColor(6, 4, board)) == false);
    }
}