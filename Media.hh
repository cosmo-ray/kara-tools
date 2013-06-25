#include <QListWidget>
#include <QListWidgetItem>
#include <QTreeWidgetItem>
#include <QString>

class	Media : public QListWidgetItem, public QTreeWidgetItem
{
public:
  Media(const QString &dirPath, const QString &name);
  Media(const QString &path);
  Media(const Media &other);
  const QString &getPath() const;
  const QString getName() const;
  int	getDuration(void) const;
  float	getFps(void) const;
  
  void	setFps(float fps);
  void	setDuration(int64_t duration);
  

private:
  QString	_path;
  int64_t _duration;
  float	_fps;
};
