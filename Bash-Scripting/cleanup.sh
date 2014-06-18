#!/bin/bash

# Cleanup
# Run as root.

LOG_DIR=/var/log
ROOT_UID=0   # Only users with $UDI 0 have root privileges.
LINES=50     # Default number of lines saved.
E_XCD=86     # Can't change directory?
E_NOTROOT=87 # Non-root exit error.


if [ "$UID" -ne "$ROOT_UID" ]
then
    echo "Must be root to run this script."
    exit $E_NOTROOT
if

if [ -n "$1" ] # Check for command-line arguments
then
    lines=$1
else
    lines=$LINES #Default
fi

cd $LOG_DIR

if [ 'pwd' != "$LOG_DIR" ] # if [ "$PWD" != "$LOG_DIR" ]
then                       # Not in /var/log?
    echo "Can't change to $LOG_DIR."
    exit $E_XCD
fi

tail -n $lines messages > mesg.temp
mv mesg.temp messages

# cat /dev/null > messages  --Above is safer
cat /dev/null > wtmp 

echo "Log files cleaned up."

exit 0
