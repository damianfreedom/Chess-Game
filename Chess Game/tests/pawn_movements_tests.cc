#include <catch2/catch.hpp>

#include <board.h>

using chess::Board;
using chess::Piece;

TEST_CASE("Valid First Move") {

    Board board = Board();
    board.SetStartingPosition();

    SECTION("Double space first move jump") {

        SECTION("White") {
            if (board.get_board()[6][0]->Move(4, 0, board) &&
                board.get_board()[6][0]->CheckPossibleMove(4, 0, board) &&
                board.get_board()[6][0]->CheckSameColor(4, 0, board)) {
                board.get_board()[6][0]->SetPosition(4, 0);
                board.get_board()[4][0]->SetPosition(6, 0);
                board.SwitchPositions(6, 0, 4, 0);
            }
            REQUIRE(board.get_board()[4][0]->get_color() == 1);
            REQUIRE(board.get_board()[6][0]->get_color() == 2);
        }

        SECTION("Black") {
            if (board.get_board()[1][0]->Move(3, 0, board) &&
                board.get_board()[1][0]->CheckPossibleMove(3, 0, board) &&
                board.get_board()[1][0]->CheckSameColor(3, 0, board)) {
                board.get_board()[1][0]->SetPosition(3, 0);
                board.get_board()[3][0]->SetPosition(1, 0);
                board.SwitchPositions(1, 0, 3, 0);
            }
            REQUIRE(board.get_board()[3][0]->get_color() == 0);
            REQUIRE(board.get_board()[1][0]->get_color() == 2);
        }
    }

    SECTION("Single space first move") {

        SECTION("White") {
            if (board.get_board()[6][0]->Move(5, 0, board) &&
                board.get_board()[6][0]->CheckPossibleMove(5, 0, board) &&
                board.get_board()[6][0]->CheckSameColor(5, 0, board)) {
                board.get_board()[6][0]->SetPosition(5, 0);
                board.get_board()[5][0]->SetPosition(6, 0);
                board.SwitchPositions(6, 0, 5, 0);
            }
            REQUIRE(board.get_board()[5][0]->get_color() == 1);
            REQUIRE(board.get_board()[6][0]->get_color() == 2);
        }

        SECTION("Black") {
            if (board.get_board()[1][0]->Move(2, 0, board) &&
                board.get_board()[1][0]->CheckPossibleMove(2, 0, board) &&
                board.get_board()[1][0]->CheckSameColor(2, 0, board)) {
                board.get_board()[1][0]->SetPosition(2, 0);
                board.get_board()[2][0]->SetPosition(1, 0);
                board.SwitchPositions(1, 0, 2, 0);
            }
            REQUIRE(board.get_board()[2][0]->get_color() == 0);
            REQUIRE(board.get_board()[1][0]->get_color() == 2);
        }
    }
}

TEST_CASE("Valid Non-First Moves") {

    Board board = Board();
    board.SetStartingPosition();

    SECTION("White Second Move") {

        //first move
        board.get_board()[6][0]->SetPosition(4, 0);
        board.get_board()[4][0]->SetPosition(6, 0);
        board.SwitchPositions(6, 0, 4, 0);

        //second move
        if (board.get_board()[4][0]->Move(3, 0, board) &&
            board.get_board()[4][0]->CheckPossibleMove(3, 0, board) &&
            board.get_board()[4][0]->CheckSameColor(3, 0, board)) {
            board.get_board()[4][0]->SetPosition(3, 0);
            board.get_board()[3][0]->SetPosition(4, 0);
            board.SwitchPositions(4, 0, 3, 0);
        }
        REQUIRE(board.get_board()[3][0]->get_color() == 1);
        REQUIRE(board.get_board()[4][0]->get_color() == 2);
    }

    SECTION("White Third Move") {
        //first move
        board.get_board()[6][0]->SetPosition(4, 0);
        board.get_board()[4][0]->SetPosition(6, 0);
        board.SwitchPositions(6, 0, 4, 0);

        //second move
        board.get_board()[4][0]->SetPosition(3, 0);
        board.get_board()[3][0]->SetPosition(4, 0);
        board.SwitchPositions(4, 0, 3, 0);

        //third move
        if (board.get_board()[3][0]->Move(2, 0, board) &&
            board.get_board()[3][0]->CheckPossibleMove(2, 0, board) &&
            board.get_board()[3][0]->CheckSameColor(2, 0, board)) {
            board.get_board()[3][0]->SetPosition(2, 0);
            board.get_board()[2][0]->SetPosition(3, 0);
            board.SwitchPositions(3, 0, 2, 0);
        }
        REQUIRE(board.get_board()[2][0]->get_color() == 1);
        REQUIRE(board.get_board()[3][0]->get_color() == 2);
    }

    SECTION("Black Second Move") {
        //first move
        board.get_board()[1][0]->SetPosition(2, 0);
        board.get_board()[2][0]->SetPosition(1, 0);
        board.SwitchPositions(1, 0, 2, 0);

        //second move
        if (board.get_board()[2][0]->Move(3, 0, board) &&
            board.get_board()[2][0]->CheckPossibleMove(3, 0, board) &&
            board.get_board()[2][0]->CheckSameColor(3, 0, board)) {
            board.get_board()[2][0]->SetPosition(3, 0);
            board.get_board()[3][0]->SetPosition(2, 0);
            board.SwitchPositions(2, 0, 3, 0);
        }
        REQUIRE(board.get_board()[3][0]->get_color() == 0);
        REQUIRE(board.get_board()[2][0]->get_color() == 2);
    }

    SECTION("Black Third Move") {
        //first move
        board.get_board()[1][0]->SetPosition(2, 0);
        board.get_board()[2][0]->SetPosition(1, 0);
        board.SwitchPositions(1, 0, 2, 0);

        //second move
        board.get_board()[2][0]->SetPosition(3, 0);
        board.get_board()[3][0]->SetPosition(2, 0);
        board.SwitchPositions(2, 0, 3, 0);

        //third move
        if (board.get_board()[3][0]->Move(4, 0, board) &&
            board.get_board()[3][0]->CheckPossibleMove(4, 0, board) &&
            board.get_board()[3][0]->CheckSameColor(4, 0, board)) {
            board.get_board()[3][0]->SetPosition(4, 0);
            board.get_board()[4][0]->SetPosition(3, 0);
            board.SwitchPositions(3, 0, 4, 0);
        }
        REQUIRE(board.get_board()[4][0]->get_color() == 0);
        REQUIRE(board.get_board()[3][0]->get_color() == 2);
    }
}

TEST_CASE("Captures") {

    Board board = Board();
    board.SetStartingPosition();

    board.get_board()[6][2]->SetPosition(4, 2);
    board.get_board()[4][2]->SetPosition(6, 2);
    board.SwitchPositions(6, 2, 4, 2);

    board.get_board()[6][4]->SetPosition(4, 4);
    board.get_board()[4][4]->SetPosition(6, 4);
    board.SwitchPositions(6, 4, 4, 4);

    board.get_board()[1][3]->SetPosition(3, 3);
    board.get_board()[3][3]->SetPosition(1, 3);
    board.SwitchPositions(1, 3, 3, 3);

    board.get_board()[1][5]->SetPosition(3, 5);
    board.get_board()[3][5]->SetPosition(1, 5);
    board.SwitchPositions(1, 5, 3, 5);

    SECTION("White") {

        SECTION("Left Diagonal") {
            REQUIRE((board.get_board()[4][4]->Move(3, 3, board) &&
                    board.get_board()[4][4]->CheckPossibleMove(3, 3, board) &&
                    board.get_board()[4][4]->CheckSameColor(3, 3, board)) == true);
        }

        SECTION("Right Diagonal") {
            REQUIRE((board.get_board()[4][4]->Move(3, 5, board) &&
                     board.get_board()[4][4]->CheckPossibleMove(3, 5, board) &&
                     board.get_board()[4][4]->CheckSameColor(3, 5, board)) == true);
        }
    }

    SECTION("Black") {

        SECTION("Left Diagonal") {
            REQUIRE((board.get_board()[3][3]->Move(4, 4, board) &&
                     board.get_board()[3][3]->CheckPossibleMove(4, 4, board) &&
                     board.get_board()[3][3]->CheckSameColor(4, 4, board)) == true);
        }

        SECTION("Right Diagonal") {
            REQUIRE((board.get_board()[3][3]->Move(4, 2, board) &&
                     board.get_board()[3][3]->CheckPossibleMove(4, 2, board) &&
                     board.get_board()[3][3]->CheckSameColor(4, 2, board)) == true);
        }
    }
}

TEST_CASE("Promotion") {

    Board board = Board();
    board.SetStartingPosition();

    SECTION("White") {
        board.get_board()[6][0]->SetPosition(4, 0);
        board.get_board()[4][0]->SetPosition(6, 0);
        board.SwitchPositions(6, 0, 4, 0);

        board.get_board()[4][0]->SetPosition(3, 0);
        board.get_board()[3][0]->SetPosition(4, 0);
        board.SwitchPositions(4, 0, 3, 0);

        board.get_board()[3][0]->SetPosition(2, 0);
        board.get_board()[2][0]->SetPosition(3, 0);
        board.SwitchPositions(3, 0, 2, 0);

        board.get_board()[2][0]->SetPosition(1, 1);
        board.get_board()[1][1]->SetPosition(2, 0);
        board.SwitchPositions(2, 0, 1, 1);

        board.get_board()[1][1]->SetPosition(0, 0);
        board.get_board()[0][0]->SetPosition(1, 1);
        board.SwitchPositions(1, 1, 0, 0);

        board.Promote(0,0);

        REQUIRE(board.get_board()[0][0]->get_picture() == "♕");
    }

    SECTION("Black") {
        board.get_board()[1][0]->SetPosition(3, 0);
        board.get_board()[3][0]->SetPosition(1, 0);
        board.SwitchPositions(1, 0, 3, 0);

        board.get_board()[3][0]->SetPosition(4, 0);
        board.get_board()[4][0]->SetPosition(3, 0);
        board.SwitchPositions(3, 0, 4, 0);

        board.get_board()[4][0]->SetPosition(5, 0);
        board.get_board()[5][0]->SetPosition(4, 0);
        board.SwitchPositions(4, 0, 5, 0);

        board.get_board()[5][0]->SetPosition(6, 1);
        board.get_board()[6][1]->SetPosition(5, 0);
        board.SwitchPositions(5, 0, 6, 1);

        board.get_board()[6][1]->SetPosition(7, 0);
        board.get_board()[7][0]->SetPosition(6, 1);
        board.SwitchPositions(6, 1, 7, 0);

        board.Promote(7,0);

        REQUIRE(board.get_board()[7][0]->get_picture() == "♛");
    }
}


TEST_CASE("Invalid Pawn Moves") {
    Board board = Board();
    board.SetStartingPosition();

    //first move
    board.get_board()[6][0]->SetPosition(4, 0);
    board.get_board()[4][0]->SetPosition(6, 0);
    board.SwitchPositions(6, 0, 4, 0);

    SECTION("Move backwards") {
        REQUIRE((board.get_board()[4][0]->Move(5, 0, board) &&
                 board.get_board()[4][0]->CheckPossibleMove(5, 0, board) &&
                 board.get_board()[4][0]->CheckSameColor(5, 0, board)) == false);
    }

    SECTION("Move right") {
        REQUIRE((board.get_board()[4][0]->Move(4, 1, board) &&
                 board.get_board()[4][0]->CheckPossibleMove(4, 1, board) &&
                 board.get_board()[4][0]->CheckSameColor(4, 1, board)) == false);
    }

    SECTION("Move diagonal - not capture") {
        REQUIRE((board.get_board()[4][0]->Move(3, 1, board) &&
                 board.get_board()[4][0]->CheckPossibleMove(3, 1, board) &&
                 board.get_board()[4][0]->CheckSameColor(3, 1, board)) == false);
    }

    SECTION("More than one square after first move") {

        SECTION("Vertical") {
            REQUIRE((board.get_board()[4][0]->Move(6, 0, board) &&
                     board.get_board()[4][0]->CheckPossibleMove(6, 0, board) &&
                     board.get_board()[4][0]->CheckSameColor(6, 0, board)) == false);
        }

        SECTION("Horizontal") {
            REQUIRE((board.get_board()[4][0]->Move(4, 5, board) &&
                     board.get_board()[4][0]->CheckPossibleMove(4, 5, board) &&
                     board.get_board()[4][0]->CheckSameColor(4, 5, board)) == false);
        }

        SECTION("Diagonal") {
            REQUIRE((board.get_board()[4][0]->Move(6, 2, board) &&
                     board.get_board()[4][0]->CheckPossibleMove(6, 2, board) &&
                     board.get_board()[4][0]->CheckSameColor(6, 2, board)) == false);
        }

        SECTION("Moving like a knight") {
            REQUIRE((board.get_board()[4][0]->Move(5, 2, board) &&
                     board.get_board()[4][0]->CheckPossibleMove(5, 2, board) &&
                     board.get_board()[4][0]->CheckSameColor(5, 2, board)) == false);
        }
    }

    SECTION("Take same color piece") {
        board.get_board()[6][1]->SetPosition(4, 1);
        board.get_board()[4][1]->SetPosition(6, 1);
        board.SwitchPositions(6, 1, 4, 1);

        board.get_board()[4][1]->SetPosition(3, 1);
        board.get_board()[3][1]->SetPosition(4, 1);
        board.SwitchPositions(4, 1, 3, 1);

        REQUIRE((board.get_board()[4][0]->Move(3, 1, board) &&
                 board.get_board()[4][0]->CheckPossibleMove(3, 1, board) &&
                 board.get_board()[4][0]->CheckSameColor(3, 1, board)) == false);
    }

    SECTION("Move through a piece on first move") {
        //putting knight in front of pawn
        board.get_board()[7][1]->SetPosition(5, 2);
        board.get_board()[5][2]->SetPosition(7, 1);
        board.SwitchPositions(7, 1, 5, 2);
        REQUIRE((board.get_board()[6][2]->Move(4, 2, board) &&
                 board.get_board()[6][2]->CheckPossibleMove(4, 2, board) &&
                 board.get_board()[6][2]->CheckSameColor(4, 2, board)) == false);
    }
}
