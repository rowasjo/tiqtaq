#include <row/tiqtaq/game.hpp>
#include <algorithm>
#include <ranges>

namespace row::tiqtaq {

namespace {

using Line = std::array<Position, dimension>;
using BoardLines = std::array<Line, 8>;  // all lines for the game

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

constexpr std::array<Cell, dimension> lineValues(Line line, Board board) {
  std::array<Cell, dimension> values;
  std::ranges::transform(line, values.begin(), [board](Position pos) { return board[pos.row][pos.col]; });
  return values;
}

constexpr bool isLineWin(const Line& line,
    const std::array<std::array<Cell, dimension>, dimension>& board,
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

}  // namespace

Game::Game() : _board{}, _game_state{GameState::Playing}, _x_is_next{true} {}

bool Game::makeMove(Position pos) {
  if (pos.row >= dimension || pos.col >= dimension) {
    throw std::out_of_range("Position is outside the board.");
  }

  if (_board[pos.row][pos.col] != Cell::Empty || _game_state != GameState::Playing) {
    return false;
  }

  _board[pos.row][pos.col] = _x_is_next ? Cell::X : Cell::O;
  _x_is_next = !_x_is_next;  // Toggle player

  _game_state = checkGameState(_board);

  return true;
}

GameState Game::state() const {
  return _game_state;
}

bool Game::xIsNext() const {
  return _x_is_next;
}

Board Game::board() const {
  return _board;
}

// compile-time tests

static_assert(checkGameState({}) == GameState::Playing);

}  // namespace row::tiqtaq
