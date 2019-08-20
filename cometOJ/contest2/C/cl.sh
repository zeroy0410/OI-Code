#!/bin/bash
	echo Compiling\ $1...
	EXEC_FILE=${1%.*}.exe
	g++ $1 -o $EXEC_FILE
	echo Running...
#	__START_S=$(date +%s)
#	__START_N=$(date +%N)
	$EXEC_FILE
#	EXT_CODE=$?
#	__END_N=$(date +%N)
#	__END_S=$(date +%s)
#	_EXEC_TIME_S=$((__END_S - __START_S))
#	_EXEC_TIME_N=$((__END_N - __START_N))
#	echo --------------------------------
#	echo Process exited after ${_EXEC_TIME_S}.${_EXEC_TIME_N} seconds with return value $EXT_CODE
