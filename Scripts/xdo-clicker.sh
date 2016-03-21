#!/bin/sh
# Clicks repeatedly on a selected window.

XDO_START=`xdotool getactivewindow`
XDO_TARGET=`xdotool selectwindow`

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
