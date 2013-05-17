#include	<iostream>
#include	<QDir>
#include	<QStringList>
#include	<stdlib.h>
#include	<unistd.h>

#include <phonon/AudioOutput>
#include <phonon/MediaObject>
#include <phonon/MediaSource>
#include <phonon/VideoWidget>
#include <phonon/VideoPlayer>

/*extern "C" {
#include	<libavformat/avformat.h>
}*/

#ifdef	WIN32
#include	<windows.h>
#endif
#include	"MainWindow.hh"

MainWindow::MainWindow() : _vbox(this),
			   _start("start"),
			   _shufle("shuffle"),
			   _pick("pick"),
			   _clearPlaylist("clear"),
			   _changeDirectory("change directory"),
			   _karaDirectory("karaoke"),
			   _eyecatchDirectory("eyecatch"),
			   _PlayerMenu("Player options"),
			   _eyecatchMenu("eyecatch options"),
			   _playMenu("play options")
{
  QDesktopWidget *desktop = QApplication::desktop();

  changePlayer(MPLAYER);
  initRand();
  resize(desktop->width(), desktop->height());
  setWindowTitle("Asamiya Saki will rape all your familly");
  setWindowIcon(QIcon("resources/sukeban_deka_icone.jpg"));
  setWindowFlags(Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint | Qt::WindowMinimizeButtonHint);
 
  _FilesList.setColumnCount(3);
  QStringList ColumnNames;
  ColumnNames << "karaoke name" << "lenght" << "saki";
  _FilesList.setHeaderLabels(ColumnNames);
  _FilesList.setColumnWidth( 0, 500 );
  _splitter.addWidget(&_FilesList);
  _splitter.addWidget(&_karaList);

  _hbox2ndOptions.addWidget(&_changeDirectory);
  _hbox2ndOptions.addWidget(&_clearPlaylist);
  _hbox2ndOptions.addWidget(&_start);

  _splitter.addWidget(&_video);

  _menuBar.addMenu(&_PlayerMenu);
  _menuBar.addMenu(&_eyecatchMenu);
  _menuBar.addMenu(&_playMenu);

  _hboxOptions.addWidget(&_menuBar);
  _hboxOptions.addWidget(&_shufle);
  _hboxOptions.addWidget(&_pick);
 _hboxOptions.addWidget(&_savePlaylistButton);
 _hboxOptions.addWidget(&_loadPlaylistButton);
_savePlaylistButton.setText("Save");
_loadPlaylistButton.setText("Load");
  
  _changePlayerLocation = _PlayerMenu.addAction("select player location");
  _selectMplayer = _PlayerMenu.addAction("select Mplayer as Player");
  _selectVLC = _PlayerMenu.addAction("select VLC as Player");
  _selectMplayer->setCheckable(true);
  _selectMplayer->setChecked(true);
  _selectVLC->setCheckable(true);

  _beginEyecatch = _eyecatchMenu.addAction("begin eyecatch");
  _beginEyecatch->setCheckable(true);
  _beginEyecatch->setChecked(true);
  _endEyecatch = _eyecatchMenu.addAction("end eyecatch");
  _endEyecatch->setCheckable(true);
  _endEyecatch->setChecked(true);

  _noDouble = _playMenu.addAction("no double ?");
  _noDouble->setCheckable(true);
  _noDouble->setChecked(true);
    
  _vbox.addLayout(&_hboxOptions);
  _vbox.addLayout(&_hbox2ndOptions);
  _vbox.addWidget(&_splitter);
  _vbox.addWidget(&_find);
  _find.hide();
  _vbox.addWidget(&_find2);
  _find2.hide();
  connector();
  readKaraDirectory();
  readEyecatchDirectory();

player =  new Phonon::VideoPlayer(Phonon::VideoCategory, &_video);
player->show();
    // player->play(QString(("/home/shun/asraf/karaoke/a.avi")));
mo=player->mediaObject();
//slider = new Phonon::SeekSlider;
    // slider->setMediaObject(mo);

    // slider->show();


/*Phonon::MediaObject *music =
     Phonon::createPlayer(Phonon::MusicCategory,
                          Phonon::MediaSource("/home/shun/mysong.mp3"));
 music->play();
*/
mp=new QProcess(0);
//QStringList args;
//QString program = "mplayer";
//QString windowId=QString::number(_video.winId());
//args << "-wid" << windowId << "-slave" << "-quiet" << "/home/shun/asraf/karaoke/a.avi";
//mp->start(program,args);
}

MainWindow::~MainWindow()
{
  delete _changePlayerLocation;
}

void	MainWindow::connector(void)
{
  connect(&_FilesList,
	  SIGNAL(itemActivated(QTreeWidgetItem *, int)),
	  this,
	  SLOT(addToPlaylist(QTreeWidgetItem *)));

  connect(&_karaList,
	  SIGNAL(itemActivated(QListWidgetItem *)),
	  this,
	  SLOT(rmItemFromKaraList(QListWidgetItem *)));

  /*actions*/
  connect(_changePlayerLocation, SIGNAL(triggered()), this, SLOT(changePlayerLocation(void)));
  connect(_selectMplayer, SIGNAL(triggered()), this, SLOT(selectMplayer(void)));
  connect(_selectVLC, SIGNAL(triggered()), this, SLOT(selectVLC(void)));

  connect(_beginEyecatch, SIGNAL(triggered()), this, SLOT(beginEyecatch(void)));
  connect(_endEyecatch, SIGNAL(triggered()), this, SLOT(endEyecatch(void)));
  connect(_noDouble, SIGNAL(triggered()), this, SLOT(noDouble(void)));

  /*button*/
  connect(&_start, SIGNAL(clicked(bool)), this, SLOT(start(void)));
  connect(&_shufle, SIGNAL(clicked(bool)), this, SLOT(shufle(void)));
  connect(&_pick, SIGNAL(clicked(bool)), this, SLOT(pick(void)));
  connect(&_clearPlaylist, SIGNAL(clicked(bool)), this, SLOT(clearPlaylist(void)));
  connect(&_changeDirectory, SIGNAL(clicked(bool)), this, SLOT(changeDirectory(void)));

  connect(&_savePlaylistButton, SIGNAL(clicked(bool)), this, SLOT(savePlaylist(void)));
 connect(&_loadPlaylistButton, SIGNAL(clicked(bool)), this, SLOT(loadPlaylist(void)));

  /*check box*/

  /* mine */
connect(&_find, SIGNAL(textEdited(QString)), this, SLOT(ctrlfedited(void)));
connect(&_find2, SIGNAL(textEdited(QString)), this, SLOT(ctrlgedited(void)));
//connect(&_video, SIGNAL(clicked(bool)), this, SLOT(onacliquesurlavideo(void)));
}

void	MainWindow::loadPlaylist()
{
std::cout << "lol";
std::cout.flush();
QString filename = QFileDialog::getOpenFileName(this, tr("Open Playlist"),
                            "/home/shun/",
                            tr("Playlist (*.pls)"));
QFile f(filename);
f.open(QIODevice::ReadOnly | QIODevice::Text);
QTextStream in(&f);
QListWidgetItem* nitem;
QString line;
std::cout << filename.toUtf8().constData();
// load data in f
while (!in.atEnd()) {
line = in.readLine();
std::cout << line.toUtf8().constData() << std::endl;
std::cout.flush();
nitem = new Media(line);
_karaList.addItem(nitem);
//newItem = new Media(static_cast<Media*>(item)->getPath());
//String line = in.readLine();
}
// end load
f.close();
}

void	MainWindow::savePlaylist()
{
int i;
QString filename = QFileDialog::getSaveFileName(this, tr("Save Playlist"),
                            "/home/shun/lastplaylist.pls",
                            tr("Playlist (*.pls)"));
QFile f(filename);
f.open(QIODevice::WriteOnly);
QTextStream out(&f);
// store data in f
for(i=0;i<_karaList.count();i++) {
//f.write(static_cast<Media*>(_karaList.item(i))->getPath().toUtf8().constData());
out << static_cast<Media*>(_karaList.item(i))->getPath().toUtf8().constData() << "\n";
}
// end store
f.close();
}

void	MainWindow::readKaraDirectory()
{
  QDir	dir(_karaDirectory);
  if (!dir.exists())
    {
      qWarning("Cannot find the karaoke directory");
      return ;
    }

  // std::cout << (dir.path() + SLASH).toLocal8Bit().constData() << std::endl;

  QStringList  filesName = dir.entryList();
  QStringList::const_iterator constIterator;
  //av_register_all();

  for (constIterator = filesName.constBegin(); constIterator != filesName.constEnd();
       ++constIterator)
    {
      if ((*constIterator).contains(".avi")
	  || (*constIterator).contains(".mkv")
	  || (*constIterator).contains(".flv")
	  || (*constIterator).contains(".mp4")
	  || (*constIterator).contains(".ogv")
	)
	{
	  /*TODO: put this in thread, because it's very long.......*/
	/*  AVFormatContext* pFormatCtx = avformat_alloc_context();
	  int64_t duration = -1;
	  if (!avformat_open_input(&pFormatCtx, (_karaDirectory.replace('/', SLASH) + QString(SLASH) + (*constIterator)).toLocal8Bit().constData(), NULL, NULL))
	    {
	//      avformat_find_stream_info(pFormatCtx, NULL);
	//      duration = pFormatCtx->duration / AV_TIME_BASE;
	      // std::cout << pFormatCtx->streams[0]->r_frame_rate.num << std::endl;
              // std::cout << pFormatCtx->streams[0]->r_frame_rate.den << std::endl;
	    }
	//  avformat_free_context(pFormatCtx);
	  // QListWidgetItem* item = new Media((dir.path() + SLASH), *constIterator);
	  // _FilesList.addItem(item);
*/	  QTreeWidgetItem* nitem = new Media((dir.path() + SLASH), *constIterator);
	  nitem->setText(0, ((Media *)nitem)->getName());
	//  nitem->setText(1, durationToString(duration));
	  _FilesList.addTopLevelItem(nitem);
	}
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

void	MainWindow::addToPlaylist(QTreeWidgetItem *item)
{
  QListWidgetItem* newItem = new Media(static_cast<Media*>(item)->getPath());
  if (!_noDouble->isChecked())
    _karaList.addItem(newItem);
  else
    {
      // std::cout << item->text().toLocal8Bit().constData() << std::endl;
      // if (_karaList.count())
      // 	std::cout << _karaList.item(0)->text().toLocal8Bit().constData() << std::endl;
      if (_karaList.findItems(static_cast<Media*>(item)->getName(), Qt::MatchCaseSensitive).empty())
	_karaList.addItem(newItem);
      else
	delete newItem;
    }
}


/*Kara list slots*/

void	MainWindow::rmItemFromKaraList(QListWidgetItem *)
{
  delete _karaList.takeItem(_karaList.currentRow());
}


/*ctrl f*/
void MainWindow::keyPressEvent(QKeyEvent *e)
{
  static bool	hasCtlrFBeenPress = false;
  static bool	hasCtlrGBeenPress = false;

  // static QString	toFind;

  if ( (e->key() == Qt::Key_F) && QApplication::keyboardModifiers() && Qt::ControlModifier)
    {
      if (!hasCtlrFBeenPress)
	{
	  _find.show();
	  _find.setFocus();
      hasCtlrFBeenPress = true;
	}
      else
	{
	  _find.hide();
      hasCtlrFBeenPress = false;
	}
    }
  if ( (e->key() == Qt::Key_G) && QApplication::keyboardModifiers() && Qt::ControlModifier)
    {
      if (!hasCtlrGBeenPress)
	{
	  _find2.show();
	  _find2.setFocus();
	  _ctrlg = -1;
      hasCtlrGBeenPress = true;
	}
      else
	{
	  _find2.hide();
      hasCtlrGBeenPress = false;
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
  if (_beginEyecatch->isChecked() | _endEyecatch->isChecked())
    {
      int	len = _eyecatchList.size();
      if (_beginEyecatch->isChecked() && len)
        {
	  listsKara += " ";
	  listsKara += "\"";
          listsKara += _eyecatchDirectory;
          listsKara += SLASH;
          listsKara += _eyecatchList[rand() % len];
          listsKara += "\"";
          listsKara += _playerOpt;
        }
         if (_endEyecatch->isChecked() && len)
        {
          endlist += " ";
          endlist += "\"";
          endlist += _eyecatchDirectory.replace('/', SLASH);
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
      // listsKara += _karaDirectory.replace('/', SLASH);
      // listsKara += SLASH;
      // listsKara += _karaList.item(i)->text();
      // std::cout << "tata" << std::endl;
      // printf("%p\n", _karaList.item(i));
      listsKara += static_cast<Media*>(_karaList.item(i))->getPath();

      listsKara += "\"";
      listsKara += _playerOpt; //" -fs -ass";
      // std::cout << listsKara.toLocal8Bit().constData() << std::endl;
      ++i;
    }
  listsKara += endlist;
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

void MainWindow::mousePressEvent(QMouseEvent *e)
{
if(e->button() == Qt::LeftButton) {
	std::cout << "clic" << mo->currentTime();
std::cout.flush();
mp->write("get_time_pos\n");
setWindowTitle(mp->readAll());
}
if(e->button() == Qt::RightButton) {
mo->seek(mo->currentTime()-1000);
}
}

void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{
if(e->button() == Qt::LeftButton) {
	std::cout << "cloc" << mo->currentTime();
std::cout.flush();
mp->write("get_time_pos\n");
setWindowTitle(mp->readAll());
}
if(e->button() == Qt::RightButton) {
mo->seek(mo->currentTime()-1000);
}
}

void MainWindow::pick(void)
{
  int	len = _FilesList.topLevelItemCount();
  if (!len)
    return;
  addToPlaylist(static_cast<Media *>(_FilesList.topLevelItem(rand() % len)));

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
// std::cout << _find.text().toUtf8().constData() << std::endl;
//QStringList sl = _find.text().split(" ");
QList<QTreeWidgetItem *> iList = _FilesList.findItems(_find.text(), Qt::MatchContains);;
int i;
 for (i = 0; i < _FilesList.topLevelItemCount(); i++)
    {
	_FilesList.topLevelItem(i)->setHidden(true);
    }
for (i = 0; i < iList.size(); i++)
    {
	iList[i]->setHidden(false);
    }
}


void MainWindow::ctrlgedited(void)
{
// std::cout << _find2.text().toUtf8().constData() << std::endl;
QList<QTreeWidgetItem *> iList = _FilesList.findItems(_find2.text(), Qt::MatchContains);
if (iList.size() > 0) {
if (_ctrlg < 0) _ctrlg = 0;
if (_ctrlg >= iList.size()) _ctrlg = iList.size()-1;
    _FilesList.setCurrentItem(iList[_ctrlg]);
}
}

void MainWindow::selectVLC(void)
{
  _selectMplayer->setChecked(false);
  _selectVLC->setChecked(true);
  changePlayer(VLC);
}

void MainWindow::selectMplayer(void)
{
  _selectMplayer->setChecked(true);
  _selectVLC->setChecked(false);
  changePlayer(MPLAYER);
}

void MainWindow::noDouble(void)
{
  // _double = !_double;
}

void MainWindow::beginEyecatch(void)
{
}

void MainWindow::endEyecatch(void)
{
}

/*------------------- !Slots methodes -------------------*/


void MainWindow::clearDirList(void)
{
  for(;;)
    {
      QTreeWidgetItem* item = _FilesList.takeTopLevelItem(0);
      if (item == NULL)
	return;
      delete item;
    }
}
