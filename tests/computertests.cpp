#include "doctest/doctest.h"
#include <row/tiqtaq/game.hpp>
#include <row/tiqtaq/computer.hpp>

using namespace row::tiqtaq;

namespace {

class ComputerLostException : public std::exception {
 public:
  const char* what() const noexcept override {
    return "Computer lost the game, which should not happen with optimal play.";
  }
};

void simulateGame(Game game, Cell computer_player) {
  if (game.state() != GameState::Playing) {
    return;
  }

  Cell current_player = game.xIsNext() ? Cell::X : Cell::O;

  if (current_player == computer_player) {
    game.makeMove(strongComputerMove(game.board()));
    simulateGame(game, computer_player);  // Recurse with the updated game state
  } else {
    // Human player's turn, simulate all possible moves
    for (auto pos : all_positions) {
      if (game.board()[pos.row][pos.col] != Cell::Empty) {
        Game next_game = game;
        next_game.makeMove({pos.row, pos.col});

        if ((next_game.state() == GameState::X_Wins && computer_player == Cell::O) ||
            (next_game.state() == GameState::O_Wins && computer_player == Cell::X)) {
          throw ComputerLostException();
        }

        simulateGame(next_game, computer_player);  // Recurse with the updated game state
      }
    }
  }
}

}  // namespace

// Note: Exhaustive verification that the computer never loses, even when using a non-cached minimax algorithm,
// completes within a few seconds.

TEST_CASE("Verify computer playing as 'X' never loses with optimal strategy") {
  Game starting_game;
  CHECK_NOTHROW(simulateGame(starting_game, Cell::X));
}

TEST_CASE("Verify computer playing as 'O' never loses with optimal strategy") {
  Game starting_game;
  CHECK_NOTHROW(simulateGame(starting_game, Cell::O));
}

TEST_CASE("Verify weakComputerMove selects the first available cell") {
  Board board = {
      BoardColumn{Cell::X, Cell::O, Cell::X},
      {Cell::O, Cell::X, Cell::Empty},
      {Cell::Empty, Cell::Empty, Cell::Empty},
  };

  Position expected = {1, 2};
  CHECK(weakComputerMove(board) == expected);
}
