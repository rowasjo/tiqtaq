#include <row/tiqtaq/computer.hpp>
#include <stdexcept>

namespace row::tiqtaq {

Position weakComputerMove(const Game& game) {
  const Board board = game.board();
  for (uint8_t row = 0; row < board_dimension; ++row) {
    for (uint8_t col = 0; col < board_dimension; ++col) {
      Position pos{row, col};
      if (board[pos.row][pos.col] == Cell::Empty) {
        return pos;
      }
    }
  }

  throw std::logic_error{"Illegal call to weakComputerMove on full board"};
}

}  // namespace row::tiqtaq
