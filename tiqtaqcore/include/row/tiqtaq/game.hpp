#pragma once

#include <array>
#include <cstdint>

namespace row::tiqtaq {

constexpr int dimension = 3;

enum class Cell : uint8_t { Empty, X, O };
enum class GameState { Playing, X_Wins, O_Wins, Draw };

struct Position {
  uint8_t row;
  uint8_t col;

  constexpr inline bool operator==(Position b) const { return row == b.row && col == b.col; }
};

using Board = std::array<std::array<Cell, dimension>, dimension>;

class Game {
 public:
  Game();

  bool makeMove(Position pos);
  GameState state() const;
  bool xIsNext() const;
  Board board() const;

 private:
  Board _board;
  bool _x_is_next;
  GameState _game_state;
};

}  // namespace row::tiqtaq
