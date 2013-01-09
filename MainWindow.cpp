#include	<iostream>
#include	<stdio.h>
#include	<QDir>
#include	<QStringList>
#include	"MainWindow.hh"

MainWindow::MainWindow() : _vbox(this), _start("start")
{
  QDesktopWidget *desktop = QApplication::desktop();
  resize(desktop->width(), desktop->height());
  setWindowTitle("Asamiya Saki rape all your familly");

  _hboxLists.addWidget(&_FilesList);
  _hboxLists.addWidget(&_karaList);

  _hboxOptions.addWidget(&_start);
  
  _vbox.addLayout(&_hboxOptions);
  _vbox.addLayout(&_hboxLists);
  connector();
  readKaraDirectory("karaoke");
}

MainWindow::~MainWindow()
{
}

void	MainWindow::connector(void)
{
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

  connect(&_karaList,
	  SIGNAL(itemActivated(QListWidgetItem *)),
	  this,
	  SLOT(rmItemFromKaraList(QListWidgetItem *)));
}


void	MainWindow::readKaraDirectory(const char *dirName)
{
  QDir	dir(dirName);
  if (!dir.exists())
    {
      qWarning("Cannot find the karaoke directory");
      return ;
    }

  QStringList  filesName = dir.entryList();
  QStringList::const_iterator constIterator;

  for (constIterator = filesName.constBegin(); constIterator != filesName.constEnd();
       ++constIterator)
    _FilesList.addItem(*constIterator);
}

/*------------------- Slots methodes -------------------*/

/*Files list slots*/

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
  _karaList.addItem(item->text());
}


/*Kara list slots*/
void	MainWindow::rmItemFromKaraList(QListWidgetItem *)
{
  _karaList.takeItem(_karaList.currentRow());
}


/*------------------- !Slots methodes -------------------*/

