#include	"core.hh"
#include	"Media.hh"

Media::Media(const QString &dirPath, const QString &name)
  : _path(dirPath + name)
{
}

Media::Media(const QString &path)
  : _path(path)
{
}

const QString &Media::getPath()
{
  return (_path);
}
