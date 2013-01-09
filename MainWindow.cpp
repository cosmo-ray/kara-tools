#include	<iostream>
#include	<stdio.h>
#include	"MainWindow.hh"

MainWindow::MainWindow() : _vbox(this)
{
  QDesktopWidget *desktop = QApplication::desktop();
  resize(desktop->width(), desktop->height());
  setWindowTitle("Asamiya Saki rape all your familly");

  _vbox.addWidget(&_FilesList);
  _vbox.addWidget(&_karaList);
  

  connect(&_FilesList,
	  SIGNAL(itemClicked(QListWidgetItem *)),
	  this,
	  SLOT(itemClicked(QListWidgetItem *)));

  connect(&_FilesList,
	  SIGNAL(itemEntered(QListWidgetItem *)),
	  this,
	  SLOT(itemEntered(QListWidgetItem *)));

  connect(&_FilesList,
	  SIGNAL(itemDoubleClicked(QListWidgetItem *)),
	  this,
	  SLOT(itemDoubleClicked(QListWidgetItem *)));

  connect(&_FilesList,
	  SIGNAL(itemActivated(QListWidgetItem *)),
	  this,
	  SLOT(itemActivated(QListWidgetItem *)));

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

void	MainWindow::itemClicked(QListWidgetItem *)
{
}


void	MainWindow::itemEntered(QListWidgetItem *)
{
}

void	MainWindow::itemDoubleClicked(QListWidgetItem *)
{
}

void	MainWindow::itemActivated(QListWidgetItem *item)
{
  std::cout << item->text().toUtf8().constData() << std::endl;
}

MainWindow::~MainWindow()
{
}

