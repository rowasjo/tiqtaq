#include <row/tiqtaq/computer.hpp>
#include <stdexcept>

namespace row::tiqtaq {

Position weakComputerMove(const Game& game) {
  // Simple strategy: first available spot
  const Board board = game.board();
  for (uint8_t row = 0; row < 3; ++row) {
    for (uint8_t col = 0; col < 3; ++col) {
      Position pos{row, col};
      if (board[pos.row][pos.col] == Cell::Empty) {
        return pos;
      }
    }
  }

  throw std::logic_error{"Illegal call to computerMove on full board"};
}

}  // namespace row::tiqtaq
