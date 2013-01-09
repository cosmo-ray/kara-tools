#ifndef	MAINWINDOW_HH
#define	MAINWINDOW_HH

#include <QApplication>
#include <QDesktopWidget>
#include <QWidget>
#include <QListWidget>
#include <QVBoxLayout>

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

private slots:
  void test();

};

#endif
