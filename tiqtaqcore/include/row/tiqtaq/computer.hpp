#pragma once

#include <row/row_tiqtaqcore_export.h>
#include <row/tiqtaq/game.hpp>

namespace row::tiqtaq {

/// Selects the computer's move using a simple "weak" strategy, choosing the first available slot.
/// @param game The current state of the game, used to assess the board and
/// decide on the move.
/// @return Position representing the computer's chosen move based on the strategy.
Position ROW_TIQTAQCORE_EXPORT weakComputerMove(const Game& game);

}  // namespace row::tiqtaq
