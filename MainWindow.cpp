#include	<iostream>
#include	<QDir>
#include	<QStringList>
#include	<stdlib.h>
#include	<unistd.h>
#ifdef	WIN32
#include	<windows.h>
#endif

#include	"MainWindow.hh"

MainWindow::MainWindow() : _vbox(this), _start("start"), _shufle("shufle"),
			   _pick("pick"), _clearPlaylist("clear"),
			   _changeDirectory("change directory"),
			   _noDouble("no double"),
			   _double(true), _beginEyecatch("begin eyecatch"), _bEye(false),
			   _endEyecatch("end eyecatch"), _eEye(false),
			   _karaDirectory("karaoke"), _eyecatchDirectory("eyecatch")
{
  QDesktopWidget *desktop = QApplication::desktop();

  changePlayer(MPLAYER);
  initRand();
  resize(desktop->width(), desktop->height());
  setWindowTitle("Asamiya Saki will rape all your familly");
  setWindowIcon(QIcon("resources/sukeban_deka_icone.jpg"));

  _hboxLists.addWidget(&_FilesList);
  _hboxLists.addWidget(&_karaList);

  _hbox2ndOptions.addWidget(&_changeDirectory);
  _hbox2ndOptions.addWidget(&_clearPlaylist);

  _hboxOptions.addWidget(&_start);
  _hboxOptions.addWidget(&_shufle);
  _hboxOptions.addWidget(&_pick);
  _hboxOptions.addWidget(&_noDouble);
  _hboxOptions.addWidget(&_beginEyecatch);
  _hboxOptions.addWidget(&_endEyecatch);
  
  _vbox.addLayout(&_hboxOptions);
  _vbox.addLayout(&_hbox2ndOptions);
  _vbox.addLayout(&_hboxLists);
  connector();
  readKaraDirectory();
  readEyecatchDirectory();
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

  /*button*/
  connect(&_start, SIGNAL(clicked(bool)), this, SLOT(start(void)));
  connect(&_shufle, SIGNAL(clicked(bool)), this, SLOT(shufle(void)));
  connect(&_pick, SIGNAL(clicked(bool)), this, SLOT(pick(void)));
  connect(&_clearPlaylist, SIGNAL(clicked(bool)), this, SLOT(clearPlaylist(void)));
  connect(&_changeDirectory, SIGNAL(clicked(bool)), this, SLOT(changeDirectory(void)));

  /*check box*/
  connect(&_noDouble, SIGNAL(stateChanged(int)), this, SLOT(noDouble(void)));
  connect(&_beginEyecatch, SIGNAL(stateChanged(int)), this, SLOT(beginEyecatch(void)));
  connect(&_endEyecatch, SIGNAL(stateChanged(int)), this, SLOT(endEyecatch(void)));
}


void	MainWindow::readKaraDirectory()
{
  QDir	dir(_karaDirectory);
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
      || (*constIterator).contains(".mp3")
      || (*constIterator).contains(".ogv")
	)
      _FilesList.addItem(*constIterator);
    }
}


void	MainWindow::readEyecatchDirectory()
{
  QDir	dir(_eyecatchDirectory);
  if (!dir.exists())
    {
      qWarning("Cannot find the eyecatch directory");
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
      || (*constIterator).contains(".ogv")
    )
      _eyecatchList.push_back(*constIterator);
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


/*ctrl f*/
void MainWindow::keyPressEvent(QKeyEvent *e)
{
  static bool	hasBeenPress = false;
  static QString	toFind;

  if ( (e->key() == Qt::Key_F) && QApplication::keyboardModifiers() && Qt::ControlModifier)
    {
      if (!hasBeenPress)
	hasBeenPress = true;
      else
	{
	  hasBeenPress = false;
	  toFind.clear();
	  clearDirList();
	  readKaraDirectory();
	}
    }
  if (hasBeenPress && toFind != "")
    {
      QList<QListWidgetItem *> iList; 
      int	i = 0;
      int	end;
 
      toFind += e->text();
      iList = _FilesList.findItems(toFind, Qt::MatchContains);
      clearDirList();
      end = iList.size();
      std::cout << e->text().toLocal8Bit().constData() << std::endl;
      std::cout << end << std::endl;
      std::cout << toFind.toLocal8Bit().constData() << std::endl;
      while (i < end)
	{
	  _FilesList.addItem(iList[i]->text());
	  ++i;
	}
    }
  else if(hasBeenPress && ((e->text()[0] >= 'a' && e->text()[0] <= 'z')
			   || (e->text()[0] >= '0' && e->text()[0] <= '9')
			   || (e->text()[0]  == ' ' || e->text()[0] == '\''))
	  )
    toFind += e->text();
}

void  MainWindow::changePlayer(int i)
{
  if (i == MPLAYER)
    {
      _playerOpt = " -fs -ass";
      _player = getPlayerCmd();
    }
  else
    {
      _playerOpt = " -f";
      _player = getPlayerCmd<VLC>();      
    }
}


/*Button slots*/

void MainWindow::start(void)
{
  int	i = 0;
  QString	listsKara;
  QString	endlist;
#ifndef WIN32
  pid_t		forkRet;

  forkRet = fork();
  if (forkRet)
    return;
#endif
  if (_bEye | _eEye)
    {
      int	len = _eyecatchList.size();
      if (_bEye && len)
        {
	  listsKara += " ";
          listsKara += "\"";
          listsKara += _eyecatchDirectory;
          listsKara += "/";
          listsKara += _eyecatchList[rand() % len];
          listsKara += "\"";
          listsKara += " -fs";
        }
         if (_eEye && len)
        {
          endlist += " ";
          endlist += "\"";
          endlist += _eyecatchDirectory;
          endlist += "/";
          endlist += _eyecatchList[rand() % len];
          endlist += "\"";
          endlist += " -fs";
        }
    }

  while (_karaList.item(i))
    {
      listsKara += " ";
<<<<<<< HEAD
      #ifndef WIN32
      listsKara += _karaDirectory;
      listsKara += "/";
      listsKara += _karaList.item(i)->text().replace(" ", "\\ ").replace("'", "\\'").replace("&", "\\&").replace("(", "\\(").replace(")", "\\)").toLocal8Bit().constData();
      #else
=======
>>>>>>> 975ae2524da813d107e20d9b629f88ff20a4c57e
      listsKara += "\"";
      listsKara += _karaDirectory.replace("/", "\\");
      listsKara += SLASH;
      listsKara += _karaList.item(i)->text();
      listsKara += "\"";
<<<<<<< HEAD
      #endif
      listsKara += " -fs -ass";
      ++i;
    }
  listsKara += endlist;
#ifdef WIN32
  system(QString(
  "\"" + _player
    + listsKara + "\""
    ).toLocal8Bit().constData()
    );
#else
 system(QString(
  _player
    + listsKara
    ).toLocal8Bit().constData()
    );
 exit(0);
#endif
=======
      listsKara += _playerOpt; //" -fs -ass";
      ++i;
    }
  execPlaylist(_player, listsKara);
>>>>>>> 975ae2524da813d107e20d9b629f88ff20a4c57e
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

void MainWindow::clearPlaylist(void)
{
  while(_karaList.takeItem(0));
}

void MainWindow::changeDirectory(void)
{
  QString path = QFileDialog::getExistingDirectory(0);

  //std::cout << path.toLocal8Bit().constData() << std::endl;
  if ( path.isNull() == false )
    {
      _karaDirectory = path;
    }
  clearDirList();
  readKaraDirectory();
}


 void MainWindow::noDouble(void)
 {
   _double = !_double;
 }

void MainWindow::beginEyecatch(void)
{
  _bEye = !_bEye;  
}

void MainWindow::endEyecatch(void)
{
  _eEye = !_eEye;  
}

/*------------------- !Slots methodes -------------------*/


void MainWindow::clearDirList(void)
{
  while(_FilesList.takeItem(0)); //should realy be optimise  
}
