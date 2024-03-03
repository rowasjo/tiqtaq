#include <row/tiqtaq/gameviewcontroller.hpp>
#include <QApplication>
#include <cstdlib>

using namespace row::tiqtaq;

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);

  const char* easy_mode_env = std::getenv("TIQTAQ_EASY_MODE");
  bool easy_mode = easy_mode_env && std::string(easy_mode_env) == "true";

  ComputerMoveFunction computer_move = easy_mode ? weakComputerMove : strongComputerMove;

  GameViewController tictactoe(std::move(computer_move));
  tictactoe.show();

  return app.exec();
}
