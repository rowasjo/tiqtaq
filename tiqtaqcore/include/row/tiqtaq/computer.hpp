#pragma once

#include <row/row_tiqtaqcore_export.h>
#include <row/tiqtaq/gametypes.hpp>

namespace row::tiqtaq {

/// Determines the optimal next move in tic-tac-toe using the minimax algorithm.
/// @param board The current state of the tic-tac-toe board, used to assess and decide on the next move.
/// @return Position representing the computer's chosen move based on the strategy.
/// @throws std::logic_error if called on a board that has ended.
Position ROW_TIQTAQCORE_EXPORT strongComputerMove(Board board);

/// Chooses the next available cell as the computer move.
/// @param board The current state of the tic-tac-toe board.
/// @return Position representing the computer's chosen move based on the strategy.
/// @throws std::logic_error if called on a board that has ended.
Position ROW_TIQTAQCORE_EXPORT weakComputerMove(Board board);

}  // namespace row::tiqtaq
