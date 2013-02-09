#ifndef	MAINWINDOW_HH
#define	MAINWINDOW_HH

#include <QApplication>
#include <QDesktopWidget>
#include <QWidget>
#include <QListWidget>
#include <QListWidgetItem>
#include <QVBoxLayout>
#include <QPushButton>
#include <QCheckBox>
#include <QKeyEvent>
#include <QFileDialog>

class	MainWindow : public QWidget
{
  Q_OBJECT
public:
  ~MainWindow();
  MainWindow();
  
private:

  QVBoxLayout _vbox;
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
  bool	      _double;
  bool	      _bEye;
  bool	      _eEye;

  MainWindow(const MainWindow &);
  const MainWindow &operator=(const MainWindow &);
  void connector(void); //methode use to place connect function
  void readKaraDirectory();
  void keyPressEvent(QKeyEvent *e);
  void clearDirList(void);

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
};

#endif
