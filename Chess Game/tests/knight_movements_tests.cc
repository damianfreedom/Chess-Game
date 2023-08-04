#include <catch2/catch.hpp>

#include <board.h>

using chess::Board;
using chess::Piece;

TEST_CASE("Valid Knight Moves") {

    Board board = Board();
    board.SetStartingPosition();

    SECTION("Valid Knight moves") {

        SECTION("Two vertical one horizontal") {
            REQUIRE((board.get_board()[7][1]->Move(5, 2, board) &&
                     board.get_board()[7][1]->CheckPossibleMove(5, 2, board) &&
                     board.get_board()[7][1]->CheckSameColor(5, 2, board)) == true);

            REQUIRE((board.get_board()[7][6]->Move(5, 5, board) &&
                     board.get_board()[7][6]->CheckPossibleMove(5, 5, board) &&
                     board.get_board()[7][6]->CheckSameColor(5, 5, board)) == true);

            REQUIRE((board.get_board()[0][1]->Move(2, 2, board) &&
                     board.get_board()[0][1]->CheckPossibleMove(2, 2, board) &&
                     board.get_board()[0][1]->CheckSameColor(2, 2, board)) == true);

            REQUIRE((board.get_board()[0][6]->Move(2, 5, board) &&
                     board.get_board()[0][6]->CheckPossibleMove(2, 5, board) &&
                     board.get_board()[0][6]->CheckSameColor(2, 5, board)) == true);
        }

        SECTION("Two horizontal one vertical") {
            //moving pawns to clear space for knight moves
            board.get_board()[6][3]->SetPosition(5, 3);
            board.get_board()[5][3]->SetPosition(6, 3);
            board.SwitchPositions(6, 3, 5, 3);

            board.get_board()[6][4]->SetPosition(5, 4);
            board.get_board()[5][4]->SetPosition(6, 4);
            board.SwitchPositions(6, 4, 5, 4);

            board.get_board()[1][3]->SetPosition(2, 3);
            board.get_board()[2][3]->SetPosition(1, 3);
            board.SwitchPositions(1, 3, 2, 3);

            board.get_board()[1][4]->SetPosition(2, 4);
            board.get_board()[2][4]->SetPosition(1, 4);
            board.SwitchPositions(1, 4, 2, 4);

            REQUIRE((board.get_board()[7][1]->Move(6, 3, board) &&
                     board.get_board()[7][1]->CheckPossibleMove(6, 3, board) &&
                     board.get_board()[7][1]->CheckSameColor(5, 2, board)) == true);

            REQUIRE((board.get_board()[7][6]->Move(6, 4, board) &&
                     board.get_board()[7][6]->CheckPossibleMove(6, 4, board) &&
                     board.get_board()[7][6]->CheckSameColor(6, 4, board)) == true);

            REQUIRE((board.get_board()[0][1]->Move(1, 3, board) &&
                     board.get_board()[0][1]->CheckPossibleMove(1, 3, board) &&
                     board.get_board()[0][1]->CheckSameColor(1, 3, board)) == true);

            REQUIRE((board.get_board()[0][6]->Move(1, 4, board) &&
                     board.get_board()[0][6]->CheckPossibleMove(1, 4, board) &&
                     board.get_board()[0][6]->CheckSameColor(1, 4, board)) == true);

        }
    }
}

TEST_CASE("Invalid Knight Moves") {

    Board board = Board();
    board.SetStartingPosition();

    SECTION("Incorrect Knight Maneuvers") {
        REQUIRE((board.get_board()[7][1]->Move(7, 3, board) &&
                 board.get_board()[7][1]->CheckPossibleMove(7, 3, board) &&
                 board.get_board()[7][1]->CheckSameColor(7, 2, board)) == false);

        REQUIRE((board.get_board()[7][6]->Move(7, 4, board) &&
                 board.get_board()[7][6]->CheckPossibleMove(7, 4, board) &&
                 board.get_board()[7][6]->CheckSameColor(7, 4, board)) == false);

        REQUIRE((board.get_board()[0][1]->Move(1, 4, board) &&
                 board.get_board()[0][1]->CheckPossibleMove(1, 4, board) &&
                 board.get_board()[0][1]->CheckSameColor(1, 4, board)) == false);

        REQUIRE((board.get_board()[0][6]->Move(2, 4, board) &&
                 board.get_board()[0][6]->CheckPossibleMove(2, 4, board) &&
                 board.get_board()[0][6]->CheckSameColor(2, 4, board)) == false);
    }

    SECTION("Taking same color piece") {
        REQUIRE((board.get_board()[7][1]->Move(6, 3, board) &&
                 board.get_board()[7][1]->CheckPossibleMove(6, 3, board) &&
                 board.get_board()[7][1]->CheckSameColor(5, 2, board)) == false);

        REQUIRE((board.get_board()[7][6]->Move(6, 4, board) &&
                 board.get_board()[7][6]->CheckPossibleMove(6, 4, board) &&
                 board.get_board()[7][6]->CheckSameColor(6, 4, board)) == false);

        REQUIRE((board.get_board()[0][1]->Move(1, 3, board) &&
                 board.get_board()[0][1]->CheckPossibleMove(1, 3, board) &&
                 board.get_board()[0][1]->CheckSameColor(1, 3, board)) == false);

        REQUIRE((board.get_board()[0][6]->Move(1, 4, board) &&
                 board.get_board()[0][6]->CheckPossibleMove(1, 4, board) &&
                 board.get_board()[0][6]->CheckSameColor(1, 4, board)) == false);
    }
}
