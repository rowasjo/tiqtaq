#include <row/tiqtaq/computer.hpp>
#include "gameutils.hpp"
#include <algorithm>
#include <limits>
#include <optional>
#include <ranges>
#include <stdexcept>

namespace row::tiqtaq {

namespace {

int boardDepth(Board board) {
  return std::ranges::count_if(board | std::views::join, [](Cell cell) { return cell == Cell::X || cell == Cell::O; });
}

constexpr std::optional<int> terminalScore(GameState state, int depth) {
  switch (state) {
    case GameState::X_Wins:
      return 10 - depth;
    case GameState::O_Wins:
      return depth - 10;
    case GameState::Draw:
      return 0;
    default:
      return std::nullopt;
  }
}

constexpr std::pair<int, std::optional<Position>> minimax(Board board, int depth, bool is_maximizing) {
  std::optional<int> terminal_score = terminalScore(checkGameState(board), depth);
  if (terminal_score) {
    return {*terminal_score, std::nullopt};
  }

  int best_score = is_maximizing ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();
  std::optional<Position> best_move = std::nullopt;

  for (auto move : all_positions) {
    if (board[move.row][move.col] != Cell::Empty) {
      continue;
    }

    Board new_board = board;
    new_board[move.row][move.col] = is_maximizing ? Cell::X : Cell::O;
    auto [score, _] = minimax(new_board, depth + 1, !is_maximizing);
    if ((is_maximizing && score > best_score) || (!is_maximizing && score < best_score)) {
      best_score = score;
      best_move = move;
    }
  }

  return {best_score, best_move};
}

}  // namespace

Position strongComputerMove(Board board) {
  int depth = boardDepth(board);
  bool is_maximizing = (depth % 2) == 0;
  std::optional move = minimax(board, boardDepth(board), is_maximizing).second;
  if (!move) {
    throw std::logic_error{"Illegal call to make computer move on a board that has ended"};
  }
  return *move;
}

Position weakComputerMove(Board board) {
  if (checkGameState(board) != GameState::Playing) {
    throw std::logic_error{"Illegal call to make computer move on a board that has ended"};
  }

  for (auto pos : all_positions) {
    if (board[pos.row][pos.col] == Cell::Empty) {
      return pos;
    }
  }

  throw std::logic_error{"Unreachable"};
}

// // compile-time tests

constexpr Board x_won_board{BoardColumn{Cell::X, Cell::X, Cell::X},  // row 1
    {Cell::O, Cell::O, Cell::Empty},                                 // row 2
    {Cell::Empty, Cell::Empty, Cell::Empty}};                        // row3

static_assert(minimax(x_won_board, 0, false).first == 10);

// Note: Compile-time evaluation of minimax on a non-finished board may hit recursion depth limits. Increasing this
// limit or switching to a non-recursive approach can enable full compile-time evaluation.

}  // namespace row::tiqtaq
