#include <QListWidget>
#include <QListWidgetItem>
#include <QTreeWidgetItem>
#include <QString>

class	Media : public QListWidgetItem, public QTreeWidgetItem
{
public:
  Media(const QString &dirPath, const QString &name);
  Media(const QString &path);
  const QString &getPath();
  const QString getName();
private:
  QString	_path;
};
