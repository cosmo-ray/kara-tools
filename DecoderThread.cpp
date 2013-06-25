#include	"MainWindow.hh"

extern "C" {
#include	<libavformat/avformat.h>
}

DecoderThread::DecoderThread(MainWindow &mW)
  : _mainWindow(mW)
{
  av_register_all();
}

DecoderThread::~DecoderThread()
{
}


void DecoderThread::run()
{
  AVFormatContext* pFormatCtx;

  for (int i = 0; i < _mainWindow.getFileList().topLevelItemCount(); ++i)
    {
      pFormatCtx = avformat_alloc_context();
      QTreeWidgetItem* nitem = _mainWindow.getFileList().topLevelItem(i);

      if (!avformat_open_input(&pFormatCtx, static_cast<Media *>(nitem)->getPath().toLocal8Bit().constData(), NULL, NULL))
	{
	  avformat_find_stream_info(pFormatCtx, NULL);
	  static_cast<Media *>(nitem)->setDuration(pFormatCtx->duration / AV_TIME_BASE);
	  static_cast<Media *>(nitem)->setFps((float)pFormatCtx->streams[0]->r_frame_rate.num /
					      (float)pFormatCtx->streams[0]->r_frame_rate.den);
	  std::cout << static_cast<Media *>(nitem)->getFps() << std::endl;
	  std::cout << pFormatCtx->streams[0]->r_frame_rate.den << std::endl;

	  nitem->setText(1, durationToString(static_cast<Media *>(nitem)->getDuration()));
	}
      avformat_free_context(pFormatCtx);
    }
  return ;
}
