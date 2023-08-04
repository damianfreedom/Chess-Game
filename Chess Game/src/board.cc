#include "space.h"
#include "board.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "king.h"
#include "queen.h"
#include "pawn.h"

namespace chess {

    std::vector<std::vector<Piece *>> Board::get_board() const {
        return board_;
    }

    void Board::SetStartingPosition() {
        board_.resize(kBoardSize);
        for (size_t row = 0; row < kBoardSize; row++) {
            board_[row].resize(kBoardSize);
        }

        //white back row
        board_[kWhiteBackRow][kAFileRookColumn] = new Rook(kWhitePiece, kWhiteBackRow, kAFileRookColumn, "♖");
        board_[kWhiteBackRow][kBFileKnightColumn] = new Knight(kWhitePiece, kWhiteBackRow, kBFileKnightColumn, "♘");
        board_[kWhiteBackRow][kCFileBishopColumn] = new Bishop(kWhitePiece, kWhiteBackRow, kCFileBishopColumn, "♗");
        board_[kWhiteBackRow][kQueenColumn] = new Queen(kWhitePiece, kWhiteBackRow, kQueenColumn, "♕");
        board_[kWhiteBackRow][kKingColumn] = new King(kWhitePiece, kWhiteBackRow, kKingColumn, "♔");
        board_[kWhiteBackRow][kFFileBishopColumn] = new Bishop(kWhitePiece, kWhiteBackRow, kFFileBishopColumn, "♗");
        board_[kWhiteBackRow][kGFileKnightColumn] = new Knight(kWhitePiece, kWhiteBackRow, kGFileKnightColumn, "♘");
        board_[kWhiteBackRow][kHFileRookColumn] = new Rook(kWhitePiece, kWhiteBackRow, kHFileRookColumn, "♖");
        //white pawns
        for (size_t col = 0; col < kBoardSize; col++) {
            board_[kBlackPawnRow][col] = new Pawn(kWhitePiece, kBlackPawnRow, col, "♙");
        }

        //black back row
        board_[kBlackBackRow][kAFileRookColumn] = new Rook(kBlackPiece, kBlackBackRow, kAFileRookColumn, "♜");
        board_[kBlackBackRow][kBFileKnightColumn] = new Knight(kBlackPiece, kBlackBackRow, kBFileKnightColumn, "♞");
        board_[kBlackBackRow][kCFileBishopColumn] = new Bishop(kBlackPiece, kBlackBackRow, kCFileBishopColumn, "♝");
        board_[kBlackBackRow][kQueenColumn] = new Queen(kBlackPiece, kBlackBackRow, kQueenColumn, "♛");
        board_[kBlackBackRow][kKingColumn] = new King(kBlackPiece, kBlackBackRow, kKingColumn, "♚");
        board_[kBlackBackRow][kFFileBishopColumn] = new Bishop(kBlackPiece, kBlackBackRow, kFFileBishopColumn, "♝");
        board_[kBlackBackRow][kGFileKnightColumn] = new Knight(kBlackPiece, kBlackBackRow, kGFileKnightColumn, "♞");
        board_[kBlackBackRow][kHFileRookColumn] = new Rook(kBlackPiece, kBlackBackRow, kHFileRookColumn, "♜");
        //black pawns
        for (size_t col = 0; col < kBoardSize; col++) {
            board_[kWhitePawnRow][col] = new Pawn(kBlackPiece, kWhitePawnRow, col, "♟︎");
        }

        //empty space
        for (size_t row = kEmptyRowBlack; row <= kEmptyRowWhite; row++) {
            for (size_t col = 0; col < kBoardSize; col++) {
                board_[row][col] = new Space(kEmptyPiece, row, col, "");
            }
        }
    }

    Board::~Board() {
        for (size_t row = 0; row < kBoardSize; row++) {
            for (size_t col = 0; col < kBoardSize; col++) {
                delete board_[row][col];
            }
        }
    }

    void Board::SwitchPositions(int x1, int y1, int x2, int y2) {
        if (board_[x2][y2]->get_color() == kEmptyPiece) {
            auto temp = board_[x1][y1];
            board_[x1][y1] = board_[x2][y2];
            board_[x2][y2] = temp;
        } else if (board_[x1][y1] != board_[x2][y2]) {
            delete board_[x2][y2];
            board_[x2][y2] = board_[x1][y1];
            board_[x1][y1] = new Space(kEmptyPiece, x1, y1, "");
        }
    }

    void Board::Promote(int row, int col) {
        if (board_[row][col]->get_color() == kBlackPiece) {
            delete board_[row][col];
            board_[row][col] = new Queen(kBlackPiece, row, col, "♛");
        } else {
            delete board_[row][col];
            board_[row][col] = new Queen(kWhitePiece, row, col, "♕");
        }
    }

    void Board::BringBackPiece(int color, int row, int col, std::string image) {
        delete board_[row][col];
        if (image == "") {
            board_[row][col] = new Space(color, row, col, image);
        } else if (image == "♛" || image == "♕") {
            board_[row][col] = new Queen(color, row, col, image);
        } else if (image == "♟︎" || image == "♙") {
            board_[row][col] = new Pawn(color, row, col, image);
        } else if (image == "♜" || image == "♖") {
            board_[row][col] = new Rook(color, row, col, image);
        } else if (image == "♞" || image == "♘") {
            board_[row][col] = new Knight(color, row, col, image);
        } else if (image == "♝" || image == "♗") {
            board_[row][col] = new Bishop(color, row, col, image);
        } else if (image == "♚" || image == "♔") {
            board_[row][col] = new King(color, row, col, image);
        }

    }
}