#include	"MainWindow.hh"

MainWindow::MainWindow() : _vbox(this)
{
  QDesktopWidget *desktop = QApplication::desktop();
  resize(desktop->width(), desktop->height());
  setWindowTitle("Asamiya Saki rape all your familly");

  _vbox.addWidget(&_FilesList);
  _vbox.addWidget(&_karaList);
}

MainWindow::~MainWindow()
{
}

