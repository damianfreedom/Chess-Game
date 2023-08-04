#include <catch2/catch.hpp>

#include <board.h>

using chess::Board;
using chess::Piece;

TEST_CASE("Valid King Moves") {

    Board board = Board();
    board.SetStartingPosition();

    //moving king to middle of board so all directions of movement can be tested
    board.get_board()[7][4]->SetPosition(4, 4);
    board.get_board()[4][4]->SetPosition(7, 4);
    board.SwitchPositions(7, 4, 4, 4);

    SECTION("One square moves") {

        SECTION("Up one") {
            REQUIRE((board.get_board()[4][4]->Move(3, 4, board) &&
                     board.get_board()[4][4]->CheckPossibleMove(3, 4, board) &&
                     board.get_board()[4][4]->CheckSameColor(3, 4, board)) == true);
        }

        SECTION("Up one right one") {
            REQUIRE((board.get_board()[4][4]->Move(3, 5, board) &&
                     board.get_board()[4][4]->CheckPossibleMove(3, 5, board) &&
                     board.get_board()[4][4]->CheckSameColor(3, 5, board)) == true);
        }

        SECTION("Up one left one") {
            REQUIRE((board.get_board()[4][4]->Move(3, 3, board) &&
                     board.get_board()[4][4]->CheckPossibleMove(3, 3, board) &&
                     board.get_board()[4][4]->CheckSameColor(3, 3, board)) == true);
        }

        SECTION("Right one") {
            REQUIRE((board.get_board()[4][4]->Move(4, 5, board) &&
                     board.get_board()[4][4]->CheckPossibleMove(4, 5, board) &&
                     board.get_board()[4][4]->CheckSameColor(4, 5, board)) == true);
        }

        SECTION("Left one") {
            REQUIRE((board.get_board()[4][4]->Move(4, 3, board) &&
                     board.get_board()[4][4]->CheckPossibleMove(4, 3, board) &&
                     board.get_board()[4][4]->CheckSameColor(4, 3, board)) == true);
        }

        SECTION("down one left one") {
            REQUIRE((board.get_board()[4][4]->Move(5, 3, board) &&
                     board.get_board()[4][4]->CheckPossibleMove(5, 3, board) &&
                     board.get_board()[4][4]->CheckSameColor(5, 3, board)) == true);
        }

        SECTION("Down one") {
            REQUIRE((board.get_board()[4][4]->Move(5, 4, board) &&
                     board.get_board()[4][4]->CheckPossibleMove(5, 4, board) &&
                     board.get_board()[4][4]->CheckSameColor(5, 4, board)) == true);
        }

        SECTION("Down one right one") {
            REQUIRE((board.get_board()[4][4]->Move(5, 5, board) &&
                     board.get_board()[4][4]->CheckPossibleMove(5, 5, board) &&
                     board.get_board()[4][4]->CheckSameColor(5, 5, board)) == true);
        }
    }

    SECTION("Capture") {
        board.get_board()[1][3]->SetPosition(3, 3);
        board.get_board()[3][3]->SetPosition(1, 3);
        board.SwitchPositions(1, 3, 3, 3);

        REQUIRE((board.get_board()[4][4]->Move(3, 3, board) &&
                 board.get_board()[4][4]->CheckPossibleMove(3, 3, board) &&
                 board.get_board()[4][4]->CheckSameColor(3, 3, board)) == true);
    }

    SECTION("Castling") {
        /* Can not be tested because it requires features and methods from Game class.
         * Otherwise there would be sections on king and queen side castling from black and white.
         */
    }
}

TEST_CASE("Invalid King Moves") {

    Board board = Board();
    board.SetStartingPosition();

    //moving king to middle of board so all directions of movement can be tested
    board.get_board()[7][4]->SetPosition(4, 4);
    board.get_board()[4][4]->SetPosition(7, 4);
    board.SwitchPositions(7, 4, 4, 4);

    SECTION("Knight move") {
        REQUIRE((board.get_board()[4][4]->Move(6, 5, board) &&
                 board.get_board()[4][4]->CheckPossibleMove(6, 5, board) &&
                 board.get_board()[4][4]->CheckSameColor(6, 5, board)) == false);
    }

    SECTION("Two space move") {
        REQUIRE((board.get_board()[4][4]->Move(6, 4, board) &&
                 board.get_board()[4][4]->CheckPossibleMove(6, 4, board) &&
                 board.get_board()[4][4]->CheckSameColor(6, 4, board)) == false);

        REQUIRE((board.get_board()[4][4]->Move(4, 6, board) &&
                 board.get_board()[4][4]->CheckPossibleMove(4, 6, board) &&
                 board.get_board()[4][4]->CheckSameColor(4, 6, board)) == false);

        REQUIRE((board.get_board()[4][4]->Move(2, 4, board) &&
                 board.get_board()[4][4]->CheckPossibleMove(2, 4, board) &&
                 board.get_board()[4][4]->CheckSameColor(2, 4, board)) == false);

        REQUIRE((board.get_board()[4][4]->Move(4, 2, board) &&
                 board.get_board()[4][4]->CheckPossibleMove(4, 2, board) &&
                 board.get_board()[4][4]->CheckSameColor(4, 2, board)) == false);
    }

    SECTION("Take same colored piece") {
        REQUIRE((board.get_board()[0][4]->Move(1, 4, board) &&
                 board.get_board()[0][4]->CheckPossibleMove(1, 4, board) &&
                 board.get_board()[0][4]->CheckSameColor(1, 4, board)) == false);

        REQUIRE((board.get_board()[0][4]->Move(0, 5, board) &&
                 board.get_board()[0][4]->CheckPossibleMove(0, 5, board) &&
                 board.get_board()[0][4]->CheckSameColor(0, 5, board)) == false);
    }
}