#ifndef	MAINWINDOW_HH
#define	MAINWINDOW_HH

#include <QApplication>
#include <QDesktopWidget>
#include <QWidget>
#include <QListWidget>
#include <QListWidgetItem>
#include <QVBoxLayout>
#include <QDir>
class	MainWindow : public QWidget
{
  Q_OBJECT
public:
  ~MainWindow();
  MainWindow();
  
private:

  QHBoxLayout _vbox;
  QListWidget _FilesList;
  QListWidget _karaList;
  MainWindow(const MainWindow &);
  const MainWindow &operator=(const MainWindow &);
  void	connector(void); //methode use to place connect function
  void  readKaraDirectory(const char *);

private slots:
  void itemEntered(QListWidgetItem *);
  void itemDoubleClicked(QListWidgetItem *);
  void itemActivated(QListWidgetItem *);
  void itemClicked(QListWidgetItem *);
};

#endif
