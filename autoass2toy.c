#include <libavformat/avformat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

void main(int argc, char **argv) {
  float fps = 0;
  int i, j;
  int lastdot = -1;
  char fpsstring[50];
  char ass[500];
  char as1[500] = "./ass2toy ";
  char as2[500] = "./generatoy ";
  strcpy(ass,argv[1]);
  for(i = 0;ass[i]!='\0'; ++i)
	if (ass[i]=='.')
		lastdot = i;
  ass[lastdot+1]='a';
  ass[lastdot+2]='s';
  ass[lastdot+3]='s';
  ass[lastdot+4]='\0';
  av_register_all();
  AVFormatContext* pFormatCtx = avformat_alloc_context();
    if (!avformat_open_input(&pFormatCtx, argv[1], NULL, NULL))
    {
      avformat_find_stream_info(pFormatCtx, NULL);
      fps = (float)pFormatCtx->streams[0]->r_frame_rate.num / (float)pFormatCtx->streams[0]->r_frame_rate.den;
      avformat_close_input (&pFormatCtx);
      sprintf(fpsstring,"%f",fps);
      for(i=0;ass[i]!='\0';++i)
	as1[i+10]=ass[i];
      as1[i+10]=' ';
      j = i + 11;
      for(i=0;fpsstring[i]!='\0';++i)
	as1[j+i]=fpsstring[i];
      as1[j+i]='\0';
      //execl("ass2toy","ass2toy",ass,fpsstring,NULL);
      system(as1);
      for(i=0;ass[i]!='\0';++i)
	as2[i+12]=ass[i];
      system(as2);
    }
    avformat_free_context(pFormatCtx);
}
