#!/bin/sh

PROC=`ps | grep signal-games | awk  '{print $1}'`
/bin/kill -s SIGUSR2 $PROC
