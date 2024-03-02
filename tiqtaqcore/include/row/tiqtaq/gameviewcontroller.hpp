#include <row/row_tiqtaqcore_export.h>
#include <row/tiqtaq/computer.hpp>
#include <row/tiqtaq/game.hpp>
#include <QtWidgets>

namespace row::tiqtaq {

class ROW_TIQTAQCORE_EXPORT GameViewController : public QWidget {
  Q_OBJECT

 public:
  GameViewController(QWidget* parent = nullptr);

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

}  // namespace row::tiqtaq
