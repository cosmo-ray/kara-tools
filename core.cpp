#include <QDir>
#include <QString>
#include <QDebug>

#include	"core.hh"


template	<>
QString  getPlayerCmd<VLC>()
{
  return ("vlc");
}

template	<>
QString  getPlayerCmd<MPLAYER>()
{
  // std::cout << "still alive" << std::endl;
#ifdef	Q_OS_WIN32
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
#ifdef	Q_OS_WIN32
  srand(153);
#else
  srand(time(0));
#endif
}
 
void    toWinPath(QString &path)
{
#ifdef	Q_OS_WIN32
    path = path.replace("/", "\\");
#else
    (void) path;
#endif
}

 void	execPlaylist(const QString &player, const QString &listsKara)
{
#ifdef Q_OS_WIN32
  system(QString(
  QString("\"") + "\"" + player + "\""
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

 bool isAlphaNum(QCharRef c)
 {
 return ((c >= 'a' && c <= 'z')
         || (c >= '0' && c <= '9')
         || (c  == ' ' || c == '\'')
         || (c >= 'A' && c <= 'Z'));
 }

