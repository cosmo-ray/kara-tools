#include <QDir>
#include <QString>
#include <QDebug>

#include	"core.hh"

QString  getPlayerCmd()
{
  // std::cout << "still alive" << std::endl;
#ifdef	WIN32
    QString ret = "\"" + QDir::currentPath().replace("/", "\\");

  ret += "\\mplayer";
  ret += "\"";
  return (ret);
#else
  QString ret = QDir::currentPath().replace("/", "\\");

  return ("mplayer");
#endif
}

void	initRand()
{
#ifdef	WIN32
  srand(153);
#else
  srand(time(0));
#endif
}
 
 void	execPlaylist(const QString &player, const QString &listsKara)
{
#ifdef WIN32
  system(QString(
  "\"" + player
    + listsKara + "\""
    ).toLocal8Bit().constData()
    );
#else
  system(QString(
  player
    + listsKara
    ).toLocal8Bit().constData()
    );
  exit(0);
#endif
}
