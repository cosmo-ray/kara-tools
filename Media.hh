#include <QListWidget>
#include <QListWidgetItem>
#include <QString>

class	Media : public QListWidgetItem
{
public:
  Media(const QString &dirPath, const QString &name);
  Media(const QString &path);
  const QString &getPath();
private:
  QString	_path;
};
