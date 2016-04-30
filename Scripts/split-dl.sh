#/bin/sh

URL=$1
URL_NOPRE=${URL:6}
FILE_NAME=${URL_NOPRE##/*/}
BYTES=`curl -sI $1 | grep Content-Length | awk '{print $2}' | tr -d '\n'`
#HALF=$(($BYTES / 2))
HALF=5000000

curl -r0-$HALF $1 > p1 &
curl -r$HALF- $1 > p2

cat p2 >> p1
