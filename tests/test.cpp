
#include <catch2/catch_test_macros.hpp>
#include <row/tiqtaq/game.hpp>

using namespace row::tiqtaq;

TEST_CASE("Game initialization", "[Game]") {
  Game game;

  SECTION("Initial state is Playing") {
    REQUIRE(game.state() == GameState::Playing);
  }

  SECTION("Board is initially empty") {
    auto board = game.board();
    for (const auto& row : board) {
      for (const auto& cell : row) {
        REQUIRE(cell == Cell::Empty);
      }
    }
  }

  SECTION("X starts the game") {
    REQUIRE(game.xIsNext());
  }
}

TEST_CASE("Making moves", "[Game]") {
  Game game;

  SECTION("Making a valid move changes the board") {
    Position pos{0, 0};
    REQUIRE(game.makeMove(pos));
    auto board = game.board();
    REQUIRE(board[pos.row][pos.col] != Cell::Empty);
  }

  SECTION("Alternating turns") {
    game.makeMove({0, 0});
    REQUIRE(!game.xIsNext());
    game.makeMove({0, 1});
    REQUIRE(game.xIsNext());
  }

  SECTION("Making a move on an occupied cell fails") {
    Position pos{0, 0};
    game.makeMove(pos);
    REQUIRE(!game.makeMove(pos));
  }
}

TEST_CASE("Winning conditions", "[Game]") {
  Game game;

  SECTION("X wins") {
    game.makeMove({0, 0});  // X
    game.makeMove({1, 0});  // O
    game.makeMove({0, 1});  // X
    game.makeMove({1, 1});  // O
    game.makeMove({0, 2});  // X wins by completing the top row
    REQUIRE(game.state() == GameState::X_Wins);
  }

  SECTION("O wins") {
    game.makeMove({1, 0});  // X
    game.makeMove({0, 0});  // O
    game.makeMove({1, 1});  // X
    game.makeMove({0, 1});  // O
    game.makeMove({2, 2});  // X
    game.makeMove({0, 2});  // O wins by completing the top row
    REQUIRE(game.state() == GameState::O_Wins);
  }

  SECTION("Draw") {
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
    REQUIRE(game.state() == GameState::Draw);
  }
}
