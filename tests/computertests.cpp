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

int64_t simulateGame(Game game, Cell computer_player) {
  if (game.state() != GameState::Playing) {
    return 1;
  }

  Cell current_player = game.xIsNext() ? Cell::X : Cell::O;

  int64_t simulated_games = 0;
  if (current_player == computer_player) {
    game.makeMove(strongComputerMove(game.board()));
    simulated_games += simulateGame(game, computer_player);  // Recurse with the updated game state
  } else {
    // Human player's turn, simulate all possible moves
    for (auto move : all_positions) {
      if (cellAt(game.board(), move) == Cell::Empty) {
        Game next_game = game;
        next_game.makeMove(move);

        if ((next_game.state() == GameState::X_Wins && computer_player == Cell::O) ||
            (next_game.state() == GameState::O_Wins && computer_player == Cell::X)) {
          throw ComputerLostException();
        }

        simulated_games += simulateGame(next_game, computer_player);  // Recurse with the updated game state
      }
    }
  }

  return simulated_games;
}

}  // namespace

// Note: Exhaustive verification that the computer never loses, even when using a non-cached minimax algorithm,
// completes within a few seconds.

TEST_CASE("Verify computer playing as 'X' never loses with optimal strategy") {
  Game starting_game;
  int simulated_games = 0;
  CHECK_NOTHROW(simulated_games = simulateGame(starting_game, Cell::X));
  CHECK_EQ(simulated_games, 73);  // plausible given constraint of optimal play by the computer
}

TEST_CASE("Verify computer playing as 'O' never loses with optimal strategy") {
  Game starting_game;
  int simulated_games = 0;
  CHECK_NOTHROW(simulated_games = simulateGame(starting_game, Cell::O));
  CHECK_EQ(simulated_games, 569);  // plausible given constraint of optimal play by the computer
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
