#include <QtWidgets>

class TicTacToe : public QWidget {
  Q_OBJECT

 public:
  TicTacToe(QWidget* parent = nullptr);

 private slots:
  void buttonClicked();

 private:
  QPushButton* buttons[3][3];
  QLabel* statusLabel;

  void computerMove();
  void checkWinCondition();
  bool checkRowColDiag(int rowStart, int colStart, int rowStep, int colStep);
  void updateStatus();
  void disableButtons();
  bool isBoardFull();
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
}

void TicTacToe::buttonClicked() {
  QPushButton* clickedButton = qobject_cast<QPushButton*>(sender());
  if (clickedButton && clickedButton->text().isEmpty()) {
    clickedButton->setText("X");  // Player's move
    if (!isBoardFull()) {
      checkWinCondition();  // Check if player wins
      if (statusLabel->text() == "Your turn") {
        computerMove();       // Computer's move if the game is not over
        checkWinCondition();  // Check if computer wins
      }
    }
  }
}

void TicTacToe::computerMove() {
  for (int row = 0; row < 3; ++row) {
    for (int col = 0; col < 3; ++col) {
      if (buttons[row][col]->text().isEmpty()) {
        buttons[row][col]->setText("O");
        return;
      }
    }
  }
}

void TicTacToe::checkWinCondition() {
  bool hasWinner = false;
  QString winner;

  // Check rows and columns
  for (int i = 0; i < 3; ++i) {
    if (checkRowColDiag(i, 0, 0, 1)) {  // Check row
      hasWinner = true;
      winner = buttons[i][0]->text();  // Winner based on the row check
      break;
    }
    if (checkRowColDiag(0, i, 1, 0)) {  // Check column
      hasWinner = true;
      winner = buttons[0][i]->text();  // Winner based on the column check
      break;
    }
  }

  // Check primary diagonal
  if (!hasWinner && checkRowColDiag(0, 0, 1, 1)) {
    hasWinner = true;
    winner = buttons[0][0]->text();  // Winner based on the primary diagonal
  }

  // Check secondary diagonal
  if (!hasWinner && checkRowColDiag(0, 2, 1, -1)) {
    hasWinner = true;
    winner = buttons[0][2]->text();  // Winner based on the secondary diagonal
  }

  if (hasWinner) {
    if (winner == "X") {
      statusLabel->setText("You win!");
    } else {
      statusLabel->setText("You lose!");
    }
    disableButtons();
    return;
  }

  if (isBoardFull()) {
    statusLabel->setText("Draw!");
    disableButtons();
  }
}

bool TicTacToe::checkRowColDiag(int rowStart, int colStart, int rowStep, int colStep) {
  QString first = buttons[rowStart][colStart]->text();
  if (first.isEmpty())
    return false;

  for (int i = 1; i < 3; ++i) {
    if (buttons[rowStart + i * rowStep][colStart + i * colStep]->text() != first) {
      return false;
    }
  }

  return true;
}

void TicTacToe::updateStatus() {
  if (statusLabel->text().endsWith("turn")) {
    statusLabel->setText("Your turn");
  }
}

void TicTacToe::disableButtons() {
  for (int row = 0; row < 3; ++row) {
    for (int col = 0; col < 3; ++col) {
      buttons[row][col]->setEnabled(false);
    }
  }
}

bool TicTacToe::isBoardFull() {
  for (int row = 0; row < 3; ++row) {
    for (int col = 0; col < 3; ++col) {
      if (buttons[row][col]->text().isEmpty()) {
        return false;
      }
    }
  }
  return true;
}

#include "main.moc"

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);

  TicTacToe tictactoe;
  tictactoe.show();

  return app.exec();
}
