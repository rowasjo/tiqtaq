#include <row/tiqtaq/gametypes.hpp>
#include <algorithm>
#include <ranges>

namespace row::tiqtaq {

using Line = std::array<Position, board_dimension>;
using BoardLines = std::array<Line, 8>;  // All lines for the game

constexpr BoardLines board_lines = {
    Line{Position{0, 0}, Position{0, 1}, Position{0, 2}},  // Row 1
    Line{Position{1, 0}, Position{1, 1}, Position{1, 2}},  // Row 2
    Line{Position{2, 0}, Position{2, 1}, Position{2, 2}},  // Row 3
    Line{Position{0, 0}, Position{1, 0}, Position{2, 0}},  // Col 1
    Line{Position{0, 1}, Position{1, 1}, Position{2, 1}},  // Col 2
    Line{Position{0, 2}, Position{1, 2}, Position{2, 2}},  // Col 3
    Line{Position{0, 0}, Position{1, 1}, Position{2, 2}},  // Diagonal 1
    Line{Position{2, 0}, Position{1, 1}, Position{0, 2}}   // Diagonal 2
};

constexpr std::array<Cell, board_dimension> lineValues(Line line, Board board) {
  std::array<Cell, board_dimension> values;
  std::ranges::transform(line, values.begin(), [board](Position pos) { return board[pos.row][pos.col]; });
  return values;
}

constexpr bool isLineWin(const Line& line,
    const std::array<std::array<Cell, board_dimension>, board_dimension>& board,
    Cell player) {
  auto values = lineValues(line, board);
  return std::ranges::all_of(values, [player](Cell cell) { return cell == player; });
}

constexpr GameState checkGameState(Board board) {
  // Checking the entire board is cheap since it is small. For very large boards,
  // taking the move just made into account becomes relevant.

  // Check for a win for each player
  for (const auto& player : {Cell::X, Cell::O}) {
    for (const auto& line : board_lines) {
      if (isLineWin(line, board, player)) {
        return player == Cell::X ? GameState::X_Wins : GameState::O_Wins;
      }
    }
  }

  // Declaring draw when all cells are filled. For larger boards a counter could keep track of
  // number of cells filled. It is also possible to declare draw earlier when no player can win.
  bool isFull = std::ranges::all_of(board | std::views::join, [](const Cell& cell) { return cell != Cell::Empty; });
  return isFull ? GameState::Draw : GameState::Playing;
}

}  // namespace row::tiqtaq
