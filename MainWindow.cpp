#include	<iostream>
#include	<stdio.h>
#include	<string>
#include	<QDir>
#include	<QStringList>
#include	<stdlib.h>
#include	<unistd.h>
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

  connect(&_start,
	  SIGNAL(clicked(bool)),
	  this,
	  SLOT(start(void)));
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
    {
      if ((*constIterator).contains(".avi")
	  || (*constIterator).contains(".mkv")
	  || (*constIterator).contains(".flv")
	)
      _FilesList.addItem(*constIterator);
    }
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


/*Button slots*/

void MainWindow::start(void)
{
  int	i = 0;

  // chdir("./karaoke");
  while (_karaList.item(i))
    {
      system(std::string(
			 std::string("mplayer ./karaoke/")
			 + _karaList.item(i)->text().replace(" ", "\\ "
							     ).toLocal8Bit().constData()
			 + " -fs -ass"
			 ).c_str()
	     );
      ++i;
    }
}


/*------------------- !Slots methodes -------------------*/

