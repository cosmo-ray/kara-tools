#ifndef	MAINWINDOW_HH
#define	MAINWINDOW_HH

#include <QApplication>
#include <QDesktopWidget>
#include <QWidget>
#include <QListWidget>
#include <QListWidgetItem>
#include <QVBoxLayout>
#include <QPushButton>

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
  QPushButton _start;
  QPushButton _shufle;

  MainWindow(const MainWindow &);
  const MainWindow &operator=(const MainWindow &);
  void	connector(void); //methode use to place connect function
  void  readKaraDirectory(const char *);

private slots:
  /*Files list slots*/
  void itemEntered(QListWidgetItem *);
  void itemDoubleClicked(QListWidgetItem *);
  void itemActivated(QListWidgetItem *);
  void itemClicked(QListWidgetItem *);
  

  /*Kara list slots*/
  void rmItemFromKaraList(QListWidgetItem *);

  /*Button slots*/
  void start(void);
  void shufle(void);
};

#endif
