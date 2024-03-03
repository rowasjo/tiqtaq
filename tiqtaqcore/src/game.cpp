#include <row/tiqtaq/game.hpp>
#include "gameutils.hpp"
#include <stdexcept>

namespace row::tiqtaq {

Game::Game() : _board{}, _game_state{GameState::Playing}, _x_is_next{true} {}

bool Game::makeMove(Position pos) {
  if (pos.row >= board_dimension || pos.col >= board_dimension) {
    throw std::out_of_range("Position is outside the board.");
  }

  if (cellAt(_board, pos) != Cell::Empty || _game_state != GameState::Playing) {
    return false;
  }

  cellAt(_board, pos) = _x_is_next ? Cell::X : Cell::O;
  _x_is_next = !_x_is_next;  // Toggle player

  _game_state = checkGameState(_board);

  return true;
}

bool Game::xIsNext() const {
  return _x_is_next;
}

GameState Game::state() const {
  return _game_state;
}

Board Game::board() const {
  return _board;
}

// compile-time tests

static_assert(checkGameState({}) == GameState::Playing);

}  // namespace row::tiqtaq
