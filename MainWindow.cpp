#include	<iostream>
#include	<stdio.h>
#include	<string>
#include	<QDir>
#include	<QStringList>
#include	<stdlib.h>
#include	<unistd.h>
#include	"MainWindow.hh"

MainWindow::MainWindow() : _vbox(this), _start("start"), _shufle("shufle"), _pick("pick"), _noDouble("no double"), _double(true)
{
  QDesktopWidget *desktop = QApplication::desktop();

  srand(time(0));

  resize(desktop->width(), desktop->height());
  setWindowTitle("Asamiya Saki rape all your familly");

  _hboxLists.addWidget(&_FilesList);
  _hboxLists.addWidget(&_karaList);

  _hboxOptions.addWidget(&_start);
  _hboxOptions.addWidget(&_shufle);
  _hboxOptions.addWidget(&_pick);
  _hboxOptions.addWidget(&_noDouble);
  
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
	  SIGNAL(itemActivated(QListWidgetItem *)),
	  this,
	  SLOT(addToPlaylist(QListWidgetItem *)));

  connect(&_karaList,
	  SIGNAL(itemActivated(QListWidgetItem *)),
	  this,
	  SLOT(rmItemFromKaraList(QListWidgetItem *)));

  connect(&_start, SIGNAL(clicked(bool)), this, SLOT(start(void)));
  connect(&_shufle, SIGNAL(clicked(bool)), this, SLOT(shufle(void)));
  connect(&_pick, SIGNAL(clicked(bool)), this, SLOT(pick(void)));
  connect(&_noDouble, SIGNAL(stateChanged(int)), this, SLOT(noDouble(void)));
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
	  || (*constIterator).contains(".mp4")
	)
      _FilesList.addItem(*constIterator);
    }
}

/*------------------- Slots methodes -------------------*/

/*Files list slots*/

void	MainWindow::addToPlaylist(QListWidgetItem *item)
{
  if (_double)
    _karaList.addItem(item->text());
  else
    {
      if (_karaList.findItems(item->text(), Qt::MatchCaseSensitive).empty())
	_karaList.addItem(item->text());
    }
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
  std::string	listsKara;

  // chdir("./karaoke");
  while (_karaList.item(i))
    {
      listsKara += " ./karaoke/";
      listsKara += _karaList.item(i)->text().replace(" ", "\\ ").toLocal8Bit().constData();
      listsKara += " -fs -ass";
      ++i;
    }
  system(std::string(
		     std::string("mplayer ")
		     + listsKara
		     ).c_str()
	 );
}


void MainWindow::shufle(void)
{
  int	len = _karaList.count();
  int	i = 0;

  if (len < 2)
    return ;

  QListWidgetItem *tmp;

  while (i < len)
    {
      tmp = _karaList.takeItem(rand() % len);
      _karaList.insertItem(rand() % (len - 1), tmp);
      ++i;
    }
}

void MainWindow::pick(void)
{
  int	len = _FilesList.count();
  if (!len)
    return;
  addToPlaylist(_FilesList.item(rand() % len));

}


 void MainWindow::noDouble(void)
 {
   _double = !_double;
 }


/*------------------- !Slots methodes -------------------*/

