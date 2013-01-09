#include	"stdio.h"
#include	"MainWindow.hh"

MainWindow::MainWindow() : _vbox(this)
{
  QDesktopWidget *desktop = QApplication::desktop();
  resize(desktop->width(), desktop->height());
  setWindowTitle("Asamiya Saki rape all your familly");

  _vbox.addWidget(&_FilesList);
  _vbox.addWidget(&_karaList);
  
  connect(&_FilesList,
	  SIGNAL(currentItemChanged(QListWidgetItem * , QListWidgetItem *  )),
	  this,
	  SLOT(test()));

  _FilesList.addItem("toto");
  _FilesList.addItem("oto");
  _FilesList.addItem("stoto");
  _FilesList.addItem("ftoto");
  _FilesList.addItem("toto");
  _FilesList.addItem("toto");
  _FilesList.addItem("toto");
  _FilesList.addItem("dwtoto");
  _FilesList.addItem("toto");
  _FilesList.addItem("toto");
  _FilesList.addItem("toto");
  _FilesList.addItem("toto");
  _FilesList.addItem("toto");
  _FilesList.addItem("toto");
  _FilesList.addItem("toto");
  _FilesList.addItem("toto");
  _FilesList.addItem("toto");
  _FilesList.addItem("toto");
  _FilesList.addItem("toto");
  _FilesList.addItem("toto");
  _FilesList.addItem("toto");
  _FilesList.addItem("toto");
  _FilesList.addItem("toto");
  _FilesList.addItem("toto");
  _FilesList.addItem("toto");
  _FilesList.addItem("toto");
  _FilesList.addItem("toto");
  _FilesList.addItem("toto");
  _FilesList.addItem("toto");
  _FilesList.addItem("toto");
}

void	MainWindow::test()
{
  printf("toto\n");
}

MainWindow::~MainWindow()
{
}

