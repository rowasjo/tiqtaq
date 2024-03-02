#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include <row/tiqtaq/game.hpp>

using namespace row::tiqtaq;

TEST_CASE("Game initialization") {
  Game game;

  SUBCASE("Initial state is Playing") {
    CHECK(game.state() == GameState::Playing);
  }

  SUBCASE("Board is initially empty") {
    auto board = game.board();
    for (const auto& row : board) {
      for (const auto& cell : row) {
        CHECK(cell == Cell::Empty);
      }
    }
  }

  SUBCASE("X starts the game") {
    CHECK(game.xIsNext());
  }
}

TEST_CASE("Making moves") {
  Game game;

  SUBCASE("Making a valid move changes the board") {
    Position pos{0, 0};
    CHECK(game.makeMove(pos));
    auto board = game.board();
    CHECK(board[pos.row][pos.col] != Cell::Empty);
  }

  SUBCASE("Alternating turns") {
    game.makeMove({0, 0});
    CHECK(!game.xIsNext());
    game.makeMove({0, 1});
    CHECK(game.xIsNext());
  }

  SUBCASE("Making a move on an occupied cell fails") {
    Position pos{0, 0};
    game.makeMove(pos);
    CHECK(!game.makeMove(pos));
  }
}

TEST_CASE("Winning conditions") {
  Game game;

  SUBCASE("X wins") {
    game.makeMove({0, 0});  // X
    game.makeMove({1, 0});  // O
    game.makeMove({0, 1});  // X
    game.makeMove({1, 1});  // O
    game.makeMove({0, 2});  // X wins by completing the top row
    CHECK(game.state() == GameState::X_Wins);
  }

  SUBCASE("O wins") {
    game.makeMove({1, 0});  // X
    game.makeMove({0, 0});  // O
    game.makeMove({1, 1});  // X
    game.makeMove({0, 1});  // O
    game.makeMove({2, 2});  // X
    game.makeMove({0, 2});  // O wins by completing the top row
    CHECK(game.state() == GameState::O_Wins);
  }

  SUBCASE("Draw") {
    // X O X
    // O X X
    // O X O
    game.makeMove({0, 0});  // X
    game.makeMove({0, 1});  // O
    game.makeMove({0, 2});  // X
    game.makeMove({1, 0});  // O
    game.makeMove({1, 1});  // X
    game.makeMove({2, 0});  // O
    game.makeMove({1, 2});  // X
    game.makeMove({2, 2});  // O
    game.makeMove({2, 1});  // X - Last move, board is full, draw
    CHECK(game.state() == GameState::Draw);
  }
}
