#include <QtWidgets>
#include <row/tiqtaq/computer.hpp>
#include <row/tiqtaq/game.hpp>

namespace row::tiqtaq {

class TicTacToe : public QWidget {
  Q_OBJECT

 public:
  TicTacToe(QWidget* parent = nullptr);

 private slots:
  void buttonClicked();

 private:
  QPushButton* buttons[3][3];
  QLabel* statusLabel;
  Game game;

  void updateBoard();
  void updateStatus();
  void disableButtons();
};

TicTacToe::TicTacToe(QWidget* parent) : QWidget(parent) {
  QGridLayout* gridLayout = new QGridLayout;
  statusLabel = new QLabel("Your turn");
  for (int row = 0; row < 3; ++row) {
    for (int col = 0; col < 3; ++col) {
      buttons[row][col] = new QPushButton;
      buttons[row][col]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
      buttons[row][col]->setText("");
      gridLayout->addWidget(buttons[row][col], row, col);
      connect(buttons[row][col], &QPushButton::clicked, this, &TicTacToe::buttonClicked);
    }
  }

  QVBoxLayout* mainLayout = new QVBoxLayout;
  mainLayout->addWidget(statusLabel);
  mainLayout->addLayout(gridLayout);
  setLayout(mainLayout);
  setWindowTitle(tr("Tic Tac Toe"));
  updateBoard();
}

void TicTacToe::buttonClicked() {
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

void TicTacToe::updateBoard() {
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

void TicTacToe::updateStatus() {
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

void TicTacToe::disableButtons() {
  for (int row = 0; row < 3; ++row) {
    for (int col = 0; col < 3; ++col) {
      buttons[row][col]->setEnabled(false);
    }
  }
}

}  // namespace row::tiqtaq

#include "main.moc"

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);

  row::tiqtaq::TicTacToe tictactoe;
  tictactoe.show();

  return app.exec();
}
