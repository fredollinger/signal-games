#!/bin/sh

EXE=signal-games
EXE=ccpd

PROC=`ps | grep ccpd | awk  '{print $1}'`
/bin/kill -s SIGUSR2 $PROC
