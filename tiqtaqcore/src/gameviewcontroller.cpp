#include <row/tiqtaq/gameviewcontroller.hpp>

namespace row::tiqtaq {

namespace {

constexpr char row_property[] = "row";
constexpr char col_property[] = "col";
constexpr char button_type_property[] = "buttonType";
constexpr char button_type_board_cell[] = "boardCell";
constexpr char button_empty_text[] = "";

QString textFromCell(Cell cell) {
  switch (cell) {
    case Cell::X:
      return "X";
    case Cell::O:
      return "O";
    case Cell::Empty:
    default:
      return button_empty_text;
  }
}

QString statusMessageFromGameState(GameState state, bool isXNext) {
  switch (state) {
    case GameState::Playing:
      return isXNext ? QObject::tr("Your turn (X)") : QObject::tr("Computer's turn (O)");
    case GameState::X_Wins:
      return QObject::tr("You win!");
    case GameState::O_Wins:
      return QObject::tr("You lose!");
    case GameState::Draw:
      return QObject::tr("Draw!");
    default:
      return QObject::tr("Unknown state");
  }
}

}  // namespace

GameViewController::GameViewController(QWidget* parent) : QWidget(parent) {
  QGridLayout* gridLayout = new QGridLayout;
  _status_label = new QLabel("Your turn");
  for (int row = 0; row < board_dimension; ++row) {
    for (int col = 0; col < board_dimension; ++col) {
      _buttons[row][col] = new QPushButton;
      QPushButton* const button = _buttons[row][col];
      button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
      button->setText(button_empty_text);
      button->setProperty(button_type_property, button_type_board_cell);
      button->setProperty(row_property, row);
      button->setProperty(col_property, col);
      gridLayout->addWidget(button, row, col);
      connect(button, &QPushButton::clicked, this, &GameViewController::buttonClicked);
    }
  }

  QVBoxLayout* mainLayout = new QVBoxLayout;
  mainLayout->addWidget(_status_label);
  mainLayout->addLayout(gridLayout);
  setLayout(mainLayout);
  setWindowTitle(tr("Tic Tac Toe"));
  updateBoard();
}

void GameViewController::buttonClicked() {
  QPushButton* clicked_button = qobject_cast<QPushButton*>(sender());
  if (clicked_button == nullptr ||
      clicked_button->property(button_type_property).toString() != button_type_board_cell) {
    return;
  }

  int row = clicked_button->property(row_property).toInt();
  int col = clicked_button->property(col_property).toInt();
  Position pos{static_cast<uint8_t>(row), static_cast<uint8_t>(col)};

  if (!_game.makeMove(pos)) {
    return;
  }

  updateBoard();
  if (_game.state() == GameState::Playing) {
    _game.makeMove(weakComputerMove(_game));
    updateBoard();
  }
  _status_label->setText(statusMessageFromGameState(_game.state(), _game.xIsNext()));
  if (_game.state() != GameState::Playing) {
    disableButtons();
  }
}

void GameViewController::updateBoard() {
  Board board = _game.board();
  for (int row = 0; row < board_dimension; ++row) {
    for (int col = 0; col < board_dimension; ++col) {
      _buttons[row][col]->setText(textFromCell(board[row][col]));
    }
  }
}

void GameViewController::disableButtons() {
  for (auto& row : _buttons) {
    for (auto& button : row) {
      button->setEnabled(false);
    }
  }
}

}  // namespace row::tiqtaq
