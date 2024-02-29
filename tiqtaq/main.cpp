#include <QtWidgets>
#include <row/tiqtaq/dummy.hpp>

int main(int argc, char* argv[]) {
  QApplication app{argc, argv};

  QPushButton button{"Hello world"};
  button.show();

  return app.exec();
}
