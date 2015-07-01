#!/bin/sh
XDO_TARGET=18874403
XDO_START=`xdotool getactivewindow`

while true; do
    xdotool windowfocus $XDO_TARGET
    sleep 0.3
    for i in `seq 1 $1`; do
        xdotool click 1
        sleep 0.03
    done
    xdotool windowfocus $XDO_START
    sleep 1
done
