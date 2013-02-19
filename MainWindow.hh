#ifndef	MAINWINDOW_HH
#define	MAINWINDOW_HH

#include <QApplication>
#include <QDesktopWidget>
#include <QWidget>
#include <QMenuBar>
#include <QListWidget>
#include <QListWidgetItem>
#include <QVBoxLayout>
#include <QPushButton>
#include <QCheckBox>
#include <QKeyEvent>
#include <QFileDialog>
#include <QMenu>

#include "core.hh"

class	MainWindow : public QWidget
{
  Q_OBJECT
public:
  ~MainWindow();
  MainWindow();
  
private:

  QVBoxLayout _vbox;
  QMenuBar    _menuBar;
  QMenu	      _PlayerMenu;
  QAction     *_changePlayerLocation;
  QHBoxLayout _hboxLists;
  QListWidget _FilesList;
  QListWidget _karaList;
  QHBoxLayout _hboxOptions;
  QHBoxLayout _hbox2ndOptions;
  QPushButton _start;
  QPushButton _shufle;
  QPushButton _pick;
  QPushButton _clearPlaylist;
  QPushButton _changeDirectory;
  QCheckBox   _noDouble;
  QCheckBox   _beginEyecatch;
  QCheckBox   _endEyecatch;
  QString     _player;
  QString     _karaDirectory;
  QString     _eyecatchDirectory;
  QString     _playerOpt;
  QStringList _eyecatchList;
  bool	      _double;
  bool	      _bEye;
  bool	      _eEye;

  MainWindow(const MainWindow &);
  const MainWindow &operator=(const MainWindow &);
  void connector(void); //methode use to place connect function
  void readKaraDirectory();
  void readEyecatchDirectory();
  void keyPressEvent(QKeyEvent *e); /*ctrl f*/
  void clearDirList(void);
  const QString &selectSub(const QString &);

  void  changePlayer(int i);

private slots:
  /*Files list slots*/
  void addToPlaylist(QListWidgetItem *);
  
  /*Kara list slots*/
  void rmItemFromKaraList(QListWidgetItem *);

  /*Button slots*/
  void start(void);
  void shufle(void);
  void pick(void);
  void noDouble(void);
  void beginEyecatch(void);
  void endEyecatch(void);
  void clearPlaylist(void);
  void changeDirectory(void);
  void changePlayerLocation(void);
};

#endif
