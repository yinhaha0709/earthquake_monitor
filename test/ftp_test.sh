#!/bin/sh

SRCDIR=../data
DESDIR=/GZ_23212

USER=ftpuser
PASSWD="JaLuboTFufkPZ1G1QTy9I9jXYM7Md"

IP=120.55.56.36
PORT=21

FILE=Burst_201203110540_13.073_-20.829.csv

cd $SRCDIR
ftp -ivn <<EOF
open $IP $PORT
user $USER $PASSWD
binary
cd $DESDIR
lcd $SRCDIR
put $FILE
quit
EOF

[ $? -eq 0 ] && echo "Upload $FILE files to romote FTP server successful." >>$SRCDIR/upload_file.log || echo "Upload $FILE files failed, pls check." >>$SRCDIR/upload_file.log
