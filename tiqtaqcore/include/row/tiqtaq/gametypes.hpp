#pragma once

#include <row/row_tiqtaqcore_export.h>
#include <array>
#include <cstdint>

namespace row::tiqtaq {

constexpr int board_dimension = 3;

enum class Cell : uint8_t { Empty, X, O };
enum class GameState { Playing, X_Wins, O_Wins, Draw };

struct Position {
  uint8_t row;
  uint8_t col;

  constexpr inline bool operator==(Position b) const { return row == b.row && col == b.col; }
};

constexpr std::array<Position, 9> all_positions = {
    Position{0, 0},
    Position{0, 1},
    Position{0, 2},
    Position{1, 0},
    Position{1, 1},
    Position{1, 2},
    Position{2, 0},
    Position{2, 1},
    Position{2, 2},
};

using BoardColumn = std::array<Cell, board_dimension>;

using Board = std::array<BoardColumn, board_dimension>;
static_assert(sizeof(Board) == 9);

constexpr Cell& cellAt(Board& board, Position pos) {
  return board[pos.row][pos.col];
}

constexpr const Cell& cellAt(const Board& board, Position pos) {
  return board[pos.row][pos.col];
}

}  // namespace row::tiqtaq
