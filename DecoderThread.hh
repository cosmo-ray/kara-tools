#include	<QThread>

class	MainWindow;

class	DecoderThread : public QThread
{
public:
  DecoderThread(MainWindow &);
  virtual ~DecoderThread();
  void run();

private:
  
  MainWindow &_mainWindow;
};
