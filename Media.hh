#include <QString>

class	Media
{
public:
  Media(const QString &dirPath, const QString &name);
  Media(const QString &path);
  const QString &getPath();
private:
  QString	_path;
};
