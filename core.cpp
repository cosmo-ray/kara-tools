#include <QDir>
#include <QString>

#include	"core.hh"

QString  getPlayerCmd()
{
  // std::cout << "still alive" << std::endl;
#ifdef	WIN32
  return ("\"\\os a moile\\asraf-build-Desktop_Qt_5_0_1_MinGW_32bit-Release\\release\\mplayer\"");
#else
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
