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
  QFont font{};
  font.setPointSize(16);
  this->setFont(font);

  QVBoxLayout* main_layout = new QVBoxLayout(this);

  _status_label = new QLabel("Your turn", this);
  main_layout->addWidget(_status_label);

  QGridLayout* grid_layout = new QGridLayout(this);
  for (int row = 0; row < board_dimension; ++row) {
    for (int col = 0; col < board_dimension; ++col) {
      _buttons[row][col] = new QPushButton(this);
      QPushButton* const button = _buttons[row][col];
      button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
      button->setText(button_empty_text);
      button->setProperty(button_type_property, button_type_board_cell);
      button->setProperty(row_property, row);
      button->setProperty(col_property, col);
      grid_layout->addWidget(button, row, col);
      connect(button, &QPushButton::clicked, this, &GameViewController::buttonClicked);
    }
  }
  main_layout->addLayout(grid_layout);

  setLayout(main_layout);
  setWindowTitle(tr("Tic Tac Toe"));
  updateBoard();
}

void GameViewController::buttonClicked() {
  QPushButton* clicked_button = qobject_cast<QPushButton*>(sender());
  if (clicked_button == nullptr ||
      clicked_button->property(button_type_property).toString() != button_type_board_cell) {
    return;
  }

  auto row = clicked_button->property(row_property).toUInt();
  auto col = clicked_button->property(col_property).toUInt();
  if (row >= board_dimension || col >= board_dimension) {
    throw std::out_of_range("Button position is outside the board.");
  }

  if (!_game.makeMove({static_cast<uint8_t>(row), static_cast<uint8_t>(col)})) {
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
