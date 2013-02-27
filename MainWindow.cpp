#include	<iostream>
#include	<QDir>
#include	<QStringList>
#include	<stdlib.h>
#include	<unistd.h>
#ifdef	WIN32
#include	<windows.h>
#endif

#include	"MainWindow.hh"

MainWindow::MainWindow() : _vbox(this), _start("start"), _shufle("shuffle"),
			   _pick("pick"), _clearPlaylist("clear"), _PlayerMenu("Player options"),
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
  setWindowFlags(Qt::Window);

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
  
  _changePlayerLocation = _PlayerMenu.addAction("select player location");
  _selectMplayer = _PlayerMenu.addAction("select Mplayer as Player");
  _selectVLC = _PlayerMenu.addAction("select VLC as Player");

//  _ctrlfedited = _PlayerMenu.addAction("ctrlfedited");

  _menuBar.addMenu(&_PlayerMenu);

  _vbox.addWidget(&_menuBar);
  _vbox.addLayout(&_hboxOptions);
  _vbox.addLayout(&_hbox2ndOptions);
  _vbox.addLayout(&_hboxLists);
  _vbox.addWidget(&_find);
  _find.hide();
 _vbox.addWidget(&_find2);
  _find2.hide();
  connector();
  readKaraDirectory();
  readEyecatchDirectory();
}

MainWindow::~MainWindow()
{
  delete _changePlayerLocation;
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

  /*actions*/
  connect(_changePlayerLocation, SIGNAL(triggered()), this, SLOT(changePlayerLocation(void)));
  connect(_selectMplayer, SIGNAL(triggered()), this, SLOT(selectMplayer(void)));
  connect(_selectVLC, SIGNAL(triggered()), this, SLOT(selectVLC(void)));

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

  /* mine */
connect(&_find, SIGNAL(textEdited(QString)), this, SLOT(ctrlfedited(void)));
connect(&_find2, SIGNAL(textEdited(QString)), this, SLOT(ctrlgedited(void)));
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

  // static QString	toFind;

  if ( (e->key() == Qt::Key_F) && QApplication::keyboardModifiers() && Qt::ControlModifier)
    {
      if (!hasBeenPress)
	{
	  _find.show();
	  _find.setFocus();
	  hasBeenPress = true;
	}
      else
	{
	  _find.hide();
	  hasBeenPress = false;
	  // toFind.clear();
	  // clearDirList();
	  // readKaraDirectory();
	}
    }
  if ( (e->key() == Qt::Key_G) && QApplication::keyboardModifiers() && Qt::ControlModifier)
    {
      if (!hasBeenPress)
	{
	  _find2.show();
	  _find2.setFocus();
	  _ctrlg = -1;
	  hasBeenPress = true;
	}
      else
	{
	  _find2.hide();
	  hasBeenPress = false;
	  // toFind.clear();
	  // clearDirList();
	  // readKaraDirectory();
	}
    }
 if (e->key() == Qt::Key_Down ) {
_ctrlg++;
MainWindow::ctrlgedited();
}
if (e->key() == Qt::Key_Up && _ctrlg > 0) {
_ctrlg--;
MainWindow::ctrlgedited();
}
  // if (hasBeenPress && toFind != "")
  // if (hasBeenPress && toFind != "")
  //   {
  //     QList<QListWidgetItem *> iList; 
  //     int	i = 0;
  //     int	end;
 
  //     toFind += e->text();
  //     iList = _FilesList.findItems(toFind, Qt::MatchContains);
  //     clearDirList();
  //     end = iList.size();
  //     std::cout << e->text().toLocal8Bit().constData() << std::endl;
  //     std::cout << end << std::endl;
  //     std::cout << toFind.toLocal8Bit().constData() << std::endl;
  //     while (i < end)
  // 	{
  // 	  _FilesList.addItem(iList[i]->text());
  // 	  ++i;
  // 	}
  //   }
  // else if(hasBeenPress && isAlphaNum(e->text()[0]) )
  //   {
  //     std::cout << "add " << e->text().toLocal8Bit().constData()[0] << std::endl;
  //     toFind += e->text();
  //   }
}

void  MainWindow::changePlayer(int i)
{
  if (i == MPLAYER)
    {
      _playerOpt = " -fs -ass -framedrop -autosync 30 -mc 2.0 ";
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
#ifndef Q_OS_WIN32
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
          listsKara += SLASH;
          listsKara += _eyecatchList[rand() % len];
          listsKara += "\"";
          listsKara += _playerOpt;
        }
         if (_eEye && len)
        {
          endlist += " ";
          endlist += "\"";
          endlist += _eyecatchDirectory;
          endlist += SLASH;
          endlist += _eyecatchList[rand() % len];
          endlist += "\"";
          endlist += _playerOpt;
        }
    }

  while (_karaList.item(i))
    {
      listsKara += " ";
      listsKara += "\"";
      listsKara += _karaDirectory.replace('/', SLASH);
      listsKara += SLASH;
      listsKara += _karaList.item(i)->text();
      listsKara += "\"";
      listsKara += _playerOpt; //" -fs -ass";
      ++i;
    }
  execPlaylist(_player, listsKara);
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

void MainWindow::changePlayerLocation(void)
{
  QString path = QFileDialog::getOpenFileName(0);

  if ( path.isNull() == false )
    {
      //toWinPath(path);
      _player = path;
    }
}

void MainWindow::ctrlfedited(void)
{
std::cout << _find.text().toUtf8().constData() << std::endl;
//QStringList sl = _find.text().split(" ");
QList<QListWidgetItem *> iList = _FilesList.findItems(_find.text(), Qt::MatchContains);;
int i;
  for (i = 0; i < _FilesList.count(); i++)
    {
	_FilesList.item(i)->setHidden(true);
    }
for (i = 0; i < iList.size(); i++)
    {
	iList[i]->setHidden(false);
    }
}


void MainWindow::ctrlgedited(void)
{
std::cout << _find2.text().toUtf8().constData() << std::endl;
QList<QListWidgetItem *> iList = _FilesList.findItems(_find2.text(), Qt::MatchContains);
if (iList.size() > 0) {
if (_ctrlg < 0) _ctrlg = 0;
if (_ctrlg >= iList.size()) _ctrlg = iList.size()-1;
    _FilesList.setCurrentItem(iList[_ctrlg]);
}
}

void MainWindow::selectVLC(void)
{
  changePlayer(VLC);
}

void MainWindow::selectMplayer(void)
{
  changePlayer(MPLAYER);
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
