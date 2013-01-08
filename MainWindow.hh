#ifndef	MAINWINDOW_HH
#define	MAINWINDOW_HH

#include <QApplication>
#include <QDesktopWidget>
#include <QWidget>
#include <QListView>
#include <QPushButton>
#include <QVBoxLayout>

class	MainWindow : public QWidget
{
public:
  ~MainWindow();
  MainWindow();
  
private:

  QHBoxLayout _vbox;
  QListView _FilesList;
  QListView _karaList;
  MainWindow(const MainWindow &);
  const MainWindow &operator=(const MainWindow &);
};

#endif
