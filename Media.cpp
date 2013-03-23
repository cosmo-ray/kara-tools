#include	<QFileInfo>
#include	"core.hh"
#include	"Media.hh"

Media::Media(const QString &dirPath, const QString &name)
  : QListWidgetItem(name), _path(dirPath + name)
{
  std::cout << _path.toLocal8Bit().constData() << std::endl;
}

Media::Media(const QString &path)
  : QListWidgetItem(QFileInfo(path).baseName()), _path(path)
{
}

const QString &Media::getPath()
{
  std::cout << "titi" << std::endl;
  std::cout << _path.toLocal8Bit().constData() << std::endl;
  return (_path);
}
