#!/bin/sh
# Replaces the variable below with target X client ID obtained from xdotool.
VAR_NAME="XDO_TARGET"
if [ $# == 0 ];
then
    echo "Usage: focus-chooser FILES..."
    exit 1
fi

echo "Focus onto window of interest"
TARGET_ID=`xdotool selectwindow`

for var in "$@"; do
    sed s/^$VAR_NAME=.*/$VAR_NAME=$TARGET_ID/ -i $var
done;
