#!/bin/sh

EXE=signal-games
#EXE=ccpd

PROC=`ps | grep $EXE | awk  '{print $1}'`
/bin/kill -s SIGUSR2 $PROC
