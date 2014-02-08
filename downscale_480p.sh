#!/bin/sh

OLD_DIR_NAME=`date | tr ' :' '_'`_old

GET_HEIGHT="ffprobe -v 0 -show_streams \"\$i\" | grep height | awk -F'=' '{ print \$2 }'"
GET_WIDTH="ffprobe -v 0 -show_streams \"\$i\" | grep width | awk -F'=' '{ print \$2 }'"

CONVERT="ffmpeg -i \"$OLD_DIR_NAME/\$i\" -f avi -vcodec libxvid -b:v 3500k -s \$NEW_WIDTH:480 -acodec libmp3lame -ab 128000 -ar 44100 \"\$BASE\""


if [ "$#" -lt 1 ]; then
    DIR='./'
elif [ "$#" -lt  2 ] && [ -d $1 ]; then
    DIR=$1
    cd $DIR
else
    echo "Usage: $0 [DIRECTORY]"
    exit -1
fi

mkdir -v $OLD_DIR_NAME;

for i in *.avi *.mp4 *.mkv *.ogg *.flv; do 
    HEIGHT=`eval $GET_HEIGHT`
    WIDTH=`eval $GET_WIDTH`
    NEW_WIDTH=`expr $WIDTH \* 480 / $HEIGHT / 8 \* 8`
    EXT=`echo $i | awk  -F"." '{print $NF}'`
    BASE=`basename "$i" .$EXT`.avi

    if [ "$HEIGHT" -gt 500 ]; then
	mv -v "$i" $OLD_DIR_NAME;
	eval $CONVERT
    fi
done
