#pragma once

#include <row/row_tiqtaqcore_export.h>
#include <row/tiqtaq/gametypes.hpp>

namespace row::tiqtaq {

/// Manages the state and logic of a Tic-Tac-Toe game.
class ROW_TIQTAQCORE_EXPORT Game {
 public:
  Game();

  /// Attempts to make a move on the board for the current player.
  /// The player (X or O) is determined by the current state of the game, as indicated by xIsNext().
  /// @param pos The desired position for the move.
  /// @return True if the move was successfully made, false if the position was already occupied.
  /// @throws std::out_of_range If the position is outside the board dimensions.
  bool makeMove(Position pos);

  /// Determines whose turn it is to play next.
  /// @return True if it's player X's turn, false for player O's turn.
  bool xIsNext() const;

  GameState state() const;
  Board board() const;

 private:
  Board _board;
  bool _x_is_next;
  GameState _game_state;
};

}  // namespace row::tiqtaq
