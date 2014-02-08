#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#ifdef WIN32
#define AS1LENGTH 12
#define AS1STR "ass2toy.exe "
#define AS2LENGTH 14
#define AS2STR "generatoy.exe "
#else
#define AS1LENGTH 10
#define AS1STR "./ass2toy "
#define AS2LENGTH 12
#define AS2STR "./generatoy "
#endif

int main(int argc, char **argv) {
  if (argc <= 1)
  {
      printf("not enouth argument\n");
      system("pause");
      return (-1);
  }
  double fps = 0;
  int i, j;
  int lastdot = -1;
  char fpsstring[50];
  char ass[512];

  char as1[512] = AS1STR;
  char as2[512] = AS2STR;
//#endif
  ass[0] = '\"';
  strcpy(ass + 1,argv[1]);
  for(i = 0;ass[i]!='\0'; ++i)
	if (ass[i]=='.')
		lastdot = i;
  ass[lastdot+1]='a';
  ass[lastdot+2]='s';
  ass[lastdot+3]='s';
  ass[lastdot+4]='\"';
  ass[lastdot+5]='\0';
  av_register_all();


  AVFormatContext* pFormatCtx = avformat_alloc_context();
    if (!avformat_open_input(&pFormatCtx, argv[1], NULL, NULL))
    {
      avformat_find_stream_info(pFormatCtx, NULL);
      fps = (double)pFormatCtx->streams[0]->r_frame_rate.num / (double)pFormatCtx->streams[0]->r_frame_rate.den;
      sprintf(fpsstring,"\"%f\"",fps);
      for(i=0;ass[i]!='\0';++i)
        as1[i+AS1LENGTH]=ass[i];
      as1[i+AS1LENGTH]=' ';
      j = i + AS1LENGTH + 1;
      for(i=0;fpsstring[i]!='\0';++i)
        as1[j+i]=fpsstring[i];
      as1[j+i]='\0';
      //execl("ass2toy","ass2toy",ass,fpsstring,NULL);
      printf("%s\n%f\n", as1, fps);
      system(as1);
      for(i=0;ass[i]!='\0';++i)
        as2[i+AS2LENGTH]=ass[i];
      printf("%s\n", as2);
      system(as2);
    }
    avformat_free_context(pFormatCtx);
    return (0);
}
