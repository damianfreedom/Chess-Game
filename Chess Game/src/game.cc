#include "board.h"
#include "game.h"

namespace chess {

    using glm::vec2;

    Game::Game() {
        ci::app::setWindowSize(kWindowSize, kWindowSize);
        game_board_.SetStartingPosition();
    }

    void Game::draw() {
        //drawing the board
        for (size_t row = 0; row < Board::kBoardSize; ++row) {
            for (size_t col = 0; col < Board::kBoardSize; ++col) {

                if ((row + col) % 2 == 0) {
                    ci::gl::color(ci::Color("white"));
                } else {
                    ci::gl::color(ci::Color("gray"));
                }

                vec2 pixel_top_left =
                        vec2(kStartingLeftCorner, kStartingLeftCorner) + vec2(col * kTileSize, row * kTileSize);
                vec2 pixel_bottom_right = pixel_top_left + vec2(kTileSize, kTileSize);
                ci::Rectf pixel_bounding_box(pixel_top_left, pixel_bottom_right);
                ci::gl::drawSolidRect(pixel_bounding_box);

                ci::gl::color(ci::Color("black"));
                ci::gl::drawString((game_board_.get_board()[row][col]->get_picture()),
                                   vec2(kPieceCenterHorizontal + col * kTileSize,
                                        kPieceCenterVertical + row * kTileSize),
                                   ci::Color("black"),
                                   ci::Font("Arial", kFontSize));

                ci::gl::drawStrokedRect(pixel_bounding_box);
            }
        }
    }

    void Game::mouseDown(ci::app::MouseEvent event) {

        vec2 position = event.getPos();
        position -= vec2(kStartingLeftCorner, kStartingLeftCorner);
        position /= kTileSize;

        for (size_t row = 0; row < Board::kBoardSize; ++row) {
            for (size_t col = 0; col < Board::kBoardSize; ++col) {
                vec2 pixel_center = {col + kTileClickArea, row + kTileClickArea};

                if (glm::distance(position, pixel_center) <= kTileClickArea) {
                    if (current_x == -1) {
                        // ignore if the first click is an empty tile
                        if (game_board_.get_board()[row][col]->get_color() == Board::kEmptyPiece) {
                            break;
                        }
                        // if it's the first part of a move then white must play
                        if (notation_.size() % 2 == 0 &&
                            game_board_.get_board()[row][col]->get_color() != Board::kWhitePiece) {
                            break;
                        }
                        // if it's the second part of a move then black must play
                        if (notation_.size() % 2 == 1 &&
                            game_board_.get_board()[row][col]->get_color() != Board::kBlackPiece) {
                            break;
                        }
                        current_x = row;
                        current_y = col;
                    } else {

                        //king and castling
                        if (game_board_.get_board()[current_x][current_y]->get_picture() == "♔" ||
                            game_board_.get_board()[current_x][current_y]->get_picture() == "♚") {
                            if (current_y - col == 2 || col - current_y == 2) {
                                if (CheckPreviousKingMove() || CheckWhiteKingInCheck() || CheckBlackKingInCheck()) {
                                    current_x = -1;
                                    current_y = -1;
                                    break;
                                } else {
                                    HandleCastling(row, col);
                                    current_x = -1;
                                    current_y = -1;
                                    break;
                                }
                            }
                        }

                        //regular movements
                        if (game_board_.get_board()[current_x][current_y]->Move(row, col, game_board_) &&
                            game_board_.get_board()[current_x][current_y]->CheckPossibleMove(row, col,
                                                                                             game_board_) &&
                            game_board_.get_board()[current_x][current_y]->CheckSameColor(row, col, game_board_)) {
                            int save_color = game_board_.get_board()[row][col]->get_color();
                            std::string save_picture = game_board_.get_board()[row][col]->get_picture();
                            game_board_.get_board()[current_x][current_y]->SetPosition(row, col);
                            game_board_.get_board()[row][col]->SetPosition(current_x, current_y);
                            game_board_.SwitchPositions(current_x, current_y, row, col);

                            //undoing a move if the same color king is still in check
                            if (notation_.size() % 2 == 0) {
                                if (CheckWhiteKingInCheck()) {
                                    game_board_.get_board()[row][col]->SetPosition(current_x, current_y);
                                    game_board_.get_board()[current_x][current_y]->SetPosition(row, col);
                                    game_board_.SwitchPositions(row, col, current_x, current_y);
                                    game_board_.BringBackPiece(save_color, row, col, save_picture);
                                    current_x = -1;
                                    current_y = -1;
                                    break;
                                }
                            } else {

                                if (CheckBlackKingInCheck()) {
                                    game_board_.get_board()[row][col]->SetPosition(current_x, current_y);
                                    game_board_.get_board()[current_x][current_y]->SetPosition(row, col);
                                    game_board_.SwitchPositions(row, col, current_x, current_y);
                                    game_board_.BringBackPiece(save_color, row, col, save_picture);
                                    current_x = -1;
                                    current_y = -1;
                                    break;
                                }
                            }

                            //pawn promotion
                            if (CheckPawnPromotion(row, col)) {
                                game_board_.Promote(row, col);
                            }

                            //adding to notation
                            notation_.push_back(game_board_.get_board()[row][col]->get_picture() + std::to_string(row) +
                                                std::to_string(col));

                        }
                        //restarting click moves
                        current_x = -1;
                        current_y = -1;
                    }
                }
            }
        }
    }

    void Game::HandleWhiteKingSideCastle() {
        if (game_board_.get_board()[Board::kWhiteBackRow][Board::kFFileBishopColumn]->get_color() ==
            Board::kEmptyPiece &&
            game_board_.get_board()[Board::kWhiteBackRow][Board::kGFileKnightColumn]->get_color() ==
            Board::kEmptyPiece) {
            if (game_board_.get_board()[Board::kWhiteBackRow][Board::kHFileRookColumn]->get_picture() == "♖") {
                game_board_.get_board()[Board::kWhiteBackRow][Board::kKingColumn]->SetPosition(Board::kWhiteBackRow,
                                                                                               Board::kGFileKnightColumn);
                game_board_.get_board()[Board::kWhiteBackRow][Board::kHFileRookColumn]->SetPosition(
                        Board::kWhiteBackRow, Board::kFFileBishopColumn);
                game_board_.SwitchPositions(Board::kWhiteBackRow, Board::kKingColumn, Board::kWhiteBackRow,
                                            Board::kGFileKnightColumn);
                game_board_.SwitchPositions(Board::kWhiteBackRow, Board::kHFileRookColumn, Board::kWhiteBackRow,
                                            Board::kFFileBishopColumn);
            }
        }
    }

    void Game::HandleBlackKingSideCastle() {
        if (game_board_.get_board()[Board::kBlackBackRow][Board::kFFileBishopColumn]->get_color() ==
            Board::kEmptyPiece &&
            game_board_.get_board()[Board::kBlackBackRow][Board::kGFileKnightColumn]->get_color() ==
            Board::kEmptyPiece) {
            if (game_board_.get_board()[Board::kBlackBackRow][Board::kHFileRookColumn]->get_picture() == "♜") {
                game_board_.get_board()[Board::kBlackBackRow][Board::kKingColumn]->SetPosition(Board::kBlackBackRow,
                                                                                               Board::kGFileKnightColumn);
                game_board_.get_board()[Board::kBlackBackRow][Board::kHFileRookColumn]->SetPosition(
                        Board::kBlackBackRow, Board::kFFileBishopColumn);
                game_board_.SwitchPositions(Board::kBlackBackRow, Board::kKingColumn, Board::kBlackBackRow,
                                            Board::kGFileKnightColumn);
                game_board_.SwitchPositions(Board::kBlackBackRow, Board::kHFileRookColumn, Board::kBlackBackRow,
                                            Board::kFFileBishopColumn);
            }
        }
    }

    void Game::HandleWhiteQueenSideCastle() {
        if (game_board_.get_board()[Board::kWhiteBackRow][Board::kQueenColumn]->get_color() == Board::kEmptyPiece &&
            game_board_.get_board()[Board::kWhiteBackRow][Board::kCFileBishopColumn]->get_color() == Board::kEmptyPiece
            && game_board_.get_board()[Board::kWhiteBackRow][Board::kBFileKnightColumn]->get_color() ==
               Board::kEmptyPiece) {
            if (game_board_.get_board()[Board::kWhiteBackRow][Board::kAFileRookColumn]->get_picture() == "♖") {
                game_board_.get_board()[Board::kWhiteBackRow][Board::kKingColumn]->SetPosition(Board::kWhiteBackRow,
                                                                                               Board::kCFileBishopColumn);
                game_board_.get_board()[Board::kWhiteBackRow][Board::kAFileRookColumn]->SetPosition(
                        Board::kWhiteBackRow, Board::kQueenColumn);
                game_board_.SwitchPositions(Board::kWhiteBackRow, Board::kKingColumn, Board::kWhiteBackRow,
                                            Board::kCFileBishopColumn);
                game_board_.SwitchPositions(Board::kWhiteBackRow, Board::kAFileRookColumn, Board::kWhiteBackRow,
                                            Board::kQueenColumn);
            }
        }
    }

    void Game::HandleBlackQueenSideCastle() {
        if (game_board_.get_board()[Board::kBlackBackRow][Board::kQueenColumn]->get_color() == Board::kEmptyPiece &&
            game_board_.get_board()[Board::kBlackBackRow][Board::kCFileBishopColumn]->get_color() == Board::kEmptyPiece
            && game_board_.get_board()[Board::kBlackBackRow][Board::kBFileKnightColumn]->get_color() ==
               Board::kEmptyPiece) {
            if (game_board_.get_board()[Board::kBlackBackRow][Board::kAFileRookColumn]->get_picture() == "♜") {
                game_board_.get_board()[Board::kBlackBackRow][Board::kKingColumn]->SetPosition(Board::kBlackBackRow,
                                                                                               Board::kCFileBishopColumn);
                game_board_.get_board()[Board::kBlackBackRow][Board::kAFileRookColumn]->SetPosition(
                        Board::kBlackBackRow, Board::kQueenColumn);
                game_board_.SwitchPositions(Board::kBlackBackRow, Board::kKingColumn, Board::kBlackBackRow,
                                            Board::kCFileBishopColumn);
                game_board_.SwitchPositions(Board::kBlackBackRow, Board::kAFileRookColumn, Board::kBlackBackRow,
                                            Board::kQueenColumn);
            }
        }

    }

    void Game::HandleCastling(int row, int col) {
        if (game_board_.get_board()[current_x][current_y]->get_picture() == "♔" && row == Board::kWhiteBackRow &&
            col == Board::kGFileKnightColumn) {
            if (CheckKingCastleIntersection(Board::kWhiteBackRow, Board::kBlackPiece)) {
                HandleWhiteKingSideCastle();
                notation_.emplace_back("♔0-0");
            }
        } else if (game_board_.get_board()[current_x][current_y]->get_picture() == "♚" && row == Board::kBlackBackRow &&
                   col == Board::kGFileKnightColumn) {
            if (CheckKingCastleIntersection(Board::kBlackBackRow, Board::kWhitePiece)) {
                HandleBlackKingSideCastle();
                notation_.emplace_back("♚0-0");
            }
        } else if (game_board_.get_board()[current_x][current_y]->get_picture() == "♔" && row == Board::kWhiteBackRow &&
                   col == Board::kCFileBishopColumn) {
            if (CheckQueenCastleIntersection(Board::kWhiteBackRow, Board::kBlackPiece)) {
                HandleWhiteQueenSideCastle();
                notation_.emplace_back("♔0-0");
            }
        } else if (game_board_.get_board()[current_x][current_y]->get_picture() == "♚" && row == Board::kBlackBackRow &&
                   col == Board::kCFileBishopColumn) {
            if (CheckQueenCastleIntersection(Board::kBlackBackRow, Board::kWhitePiece)) {
                HandleBlackQueenSideCastle();
                notation_.emplace_back("♚0-0");
            }
        }
    }

    bool Game::CheckPreviousKingMove() {
        if (notation_.size() % 2 == 0) {
            for (const std::string &move: notation_) {
                if (move.find("♔") < move.length()) {
                    return true;
                }
            }
        }

        if (notation_.size() % 1 == 0) {
            for (const std::string &move: notation_) {
                if (move.find("♚") < move.length()) {
                    return true;
                }
            }
        }
        return false;
    }

    bool Game::CheckQueenCastleIntersection(int back_row, int opposing_color) {
        for (size_t row = 0; row < Board::kBoardSize; ++row) {
            for (size_t col = 0; col < Board::kBoardSize; ++col) {
                if (game_board_.get_board()[row][col]->get_color() == opposing_color) {
                    if ((game_board_.get_board()[row][col]->Move(back_row, Board::kQueenColumn, game_board_) &&
                         game_board_.get_board()[row][col]->CheckPossibleMove(back_row, Board::kQueenColumn,
                                                                              game_board_)) ||
                        (game_board_.get_board()[row][col]->Move(back_row, Board::kCFileBishopColumn, game_board_) &&
                         game_board_.get_board()[row][col]->CheckPossibleMove(back_row, Board::kCFileBishopColumn,
                                                                              game_board_))) {
                        return false;
                    }
                }
            }
        }
        return true;
    }


    bool Game::CheckKingCastleIntersection(int back_row, int opposing_color) {
        for (size_t row = 0; row < Board::kBoardSize; ++row) {
            for (size_t col = 0; col < Board::kBoardSize; ++col) {
                if (game_board_.get_board()[row][col]->get_color() == opposing_color) {
                    if ((game_board_.get_board()[row][col]->Move(back_row, Board::kFFileBishopColumn, game_board_) &&
                         game_board_.get_board()[row][col]->CheckPossibleMove(back_row, Board::kFFileBishopColumn,
                                                                              game_board_)) ||
                        (game_board_.get_board()[row][col]->Move(back_row, Board::kGFileKnightColumn, game_board_) &&
                         game_board_.get_board()[row][col]->CheckPossibleMove(back_row, Board::kGFileKnightColumn,
                                                                              game_board_))) {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    bool Game::CheckPawnPromotion(int row, int col) {
        if (game_board_.get_board()[row][col]->get_picture() == "♟" ||
            game_board_.get_board()[row][col]->get_picture() == "♙") {
            if (row == Board::kBlackBackRow || row == Board::kWhiteBackRow) {
                return true;
            }
        }
        return false;
    }

    bool Game::CheckWhiteKingInCheck() {
        int king_row;
        int king_col;

        for (size_t row = 0; row < Board::kBoardSize; ++row) {
            for (size_t col = 0; col < Board::kBoardSize; ++col) {
                if (game_board_.get_board()[row][col]->get_picture() == "♔") {
                    king_row = row;
                    king_col = col;
                    break;
                }
            }
        }

        for (size_t row = 0; row < Board::kBoardSize; ++row) {
            for (size_t col = 0; col < Board::kBoardSize; ++col) {
                if (game_board_.get_board()[row][col]->get_color() == Board::kBlackPiece) {
                    if (game_board_.get_board()[row][col]->Move(king_row, king_col, game_board_) &&
                        game_board_.get_board()[row][col]->CheckPossibleMove(king_row, king_col, game_board_)) {
                        return true;
                    }
                }
            }
        }
        return false;
    }

    bool Game::CheckBlackKingInCheck() {
        int king_row;
        int king_col;

        for (size_t row = 0; row < Board::kBoardSize; ++row) {
            for (size_t col = 0; col < Board::kBoardSize; ++col) {
                if (game_board_.get_board()[row][col]->get_picture() == "♚") {
                    king_row = row;
                    king_col = col;
                    break;
                }
            }
        }

        for (size_t row = 0; row < Board::kBoardSize; ++row) {
            for (size_t col = 0; col < Board::kBoardSize; ++col) {
                if (game_board_.get_board()[row][col]->get_color() == Board::kWhitePiece) {
                    if (game_board_.get_board()[row][col]->Move(king_row, king_col, game_board_) &&
                        game_board_.get_board()[row][col]->CheckPossibleMove(king_row, king_col, game_board_)) {
                        return true;
                    }
                }
            }
        }
        return false;
    }
}

