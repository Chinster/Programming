#!/bin/bash

# Show the time, date, all logged-in users and system uptime

LOG_DIR=/var/log
cd $LOG_DIR
date "+%b %d, %Y %H:%M:%S" >> logusers.temp
who >> logusers.temp
uptime >> logusers.temp
