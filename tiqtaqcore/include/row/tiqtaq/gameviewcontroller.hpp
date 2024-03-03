#include <row/row_tiqtaqcore_export.h>
#include <row/tiqtaq/computer.hpp>
#include <row/tiqtaq/game.hpp>
#include <QtWidgets>
#include <functional>

namespace row::tiqtaq {

using BoardButtons = std::array<std::array<QPushButton*, board_dimension>, board_dimension>;

using ComputerMoveFunction = std::function<Position(Board)>;

/// GameViewController serves as the view-controller for the tic-tac-toe game,
/// integrating the game logic with a graphical interface for interaction.
class ROW_TIQTAQCORE_EXPORT GameViewController : public QWidget {
  Q_OBJECT

 public:
  /// Initializes the game interface, setting up the board, connecting signals,
  /// and preparing the game for play.
  /// @param computer_move Function determining the computer's next move.
  /// @param parent The parent widget, defaulting to nullptr if not specified.
  GameViewController(ComputerMoveFunction computer_move, QWidget* parent = nullptr);

 private slots:
  /// Responds to tic-tac-toe board button clicks, processes the player's move,
  /// and subsequently triggers a computer move. Updates the game and UI state.
  void buttonClicked();

 private:
  /// Refreshes the board's UI to match the current game state.
  void updateBoard();

  /// Disables all board buttons, used after the game concludes.
  void disableButtons();

  ComputerMoveFunction _computer_move;
  BoardButtons _buttons;  ///< Represents the tic-tac-toe board cells.
  QLabel* _status_label;  ///< Displays current _game status and instructions.
  Game _game;             ///< Manages the tic-tac-toe game logic.
};

}  // namespace row::tiqtaq
