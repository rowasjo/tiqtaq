#include <QtWidgets>
#include <row/tiqtaq/gameviewcontroller.hpp>

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);

  row::tiqtaq::GameViewController tictactoe;
  tictactoe.show();

  return app.exec();
}
