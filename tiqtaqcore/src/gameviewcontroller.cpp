#include <row/tiqtaq/gameviewcontroller.hpp>

namespace row::tiqtaq {

GameViewController::GameViewController(QWidget* parent) : QWidget(parent) {
  QGridLayout* gridLayout = new QGridLayout;
  statusLabel = new QLabel("Your turn");
  for (int row = 0; row < 3; ++row) {
    for (int col = 0; col < 3; ++col) {
      buttons[row][col] = new QPushButton;
      buttons[row][col]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
      buttons[row][col]->setText("");
      gridLayout->addWidget(buttons[row][col], row, col);
      connect(buttons[row][col], &QPushButton::clicked, this, &GameViewController::buttonClicked);
    }
  }

  QVBoxLayout* mainLayout = new QVBoxLayout;
  mainLayout->addWidget(statusLabel);
  mainLayout->addLayout(gridLayout);
  setLayout(mainLayout);
  setWindowTitle(tr("Tic Tac Toe"));
  updateBoard();
}

void GameViewController::buttonClicked() {
  QPushButton* clickedButton = qobject_cast<QPushButton*>(sender());
  for (int row = 0; row < 3; ++row) {
    for (int col = 0; col < 3; ++col) {
      if (buttons[row][col] == clickedButton) {
        Position pos{static_cast<uint8_t>(row), static_cast<uint8_t>(col)};
        if (game.makeMove(pos)) {
          updateBoard();
          GameState state = game.state();
          if (state == GameState::Playing) {
            game.makeMove(computerMove(game));
            updateBoard();
            state = game.state();
          }
          updateStatus();
          if (state != GameState::Playing) {
            disableButtons();
          }
        }
        return;
      }
    }
  }
}

void GameViewController::updateBoard() {
  Board board = game.board();
  for (int row = 0; row < dimension; ++row) {
    for (int col = 0; col < dimension; ++col) {
      QString text;
      switch (board[row][col]) {
        case Cell::X:
          text = "X";
          break;
        case Cell::O:
          text = "O";
          break;
        case Cell::Empty:
          text = "";
          break;
      }
      buttons[row][col]->setText(text);
    }
  }
}

void GameViewController::updateStatus() {
  switch (game.state()) {
    case GameState::Playing:
      statusLabel->setText(game.xIsNext() ? "Your turn" : "Computer's turn");
      break;
    case GameState::X_Wins:
      statusLabel->setText("You win!");
      break;
    case GameState::O_Wins:
      statusLabel->setText("You lose!");
      break;
    case GameState::Draw:
      statusLabel->setText("Draw!");
      break;
  }
}

void GameViewController::disableButtons() {
  for (int row = 0; row < 3; ++row) {
    for (int col = 0; col < 3; ++col) {
      buttons[row][col]->setEnabled(false);
    }
  }
}

}  // namespace row::tiqtaq
