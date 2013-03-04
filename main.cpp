#include	<iostream>
#include	"MainWindow.hh"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  MainWindow   window;

  window.show();
  window.move(0,0);
  app.exec();
  return (0);
}
