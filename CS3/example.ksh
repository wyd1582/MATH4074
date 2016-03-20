#!/bin/ksh

BASEDIR=/home/tjisana/MATH4074/CS3


YEAR=`/bin/date +%Y`
MONTH=`/bin/date +%m`
TODAY=`/bin/date +%d`
HOUR=`/bin/date +%H`
MINUTE=`/bin/date +%M`
#HOUR=16
#MINUTE=20
echo "$HOUR:$MINUTE"

LISTFILE=listExample

SUBLIST=$BASEDIR/$LISTFILE
BINDIR=$BASEDIR
PROG=CS3.out
LIST=`/bin/grep -v ^# $SUBLIST | /bin/cat`

if [[ ! -d $BASEDIR ]]
then
	echo "$BASEDIR does not exist."
	exit 1
fi

# launching all programs
for item in $LIST
do
	S0=`/bin/echo $item | /usr/bin/cut -d, -f1`
	K=`/bin/echo $item | /usr/bin/cut -d, -f2`
	RFR=`/bin/echo $item | /usr/bin/cut -d, -f3`
	DIV=`/bin/echo $item | /usr/bin/cut -d, -f4`
	SIG=`/bin/echo $item | /usr/bin/cut -d, -f5`
	V=`/bin/echo $item | /usr/bin/cut -d, -f6`
	THETA=`/bin/echo $item | /usr/bin/cut -d, -f7`
	T=`/bin/echo $item | /usr/bin/cut -d, -f8`
	NSP=`/bin/echo $item | /usr/bin/cut -d, -f9`
	NTS=`/bin/echo $item | /usr/bin/cut -d, -f10`
	
	echo "$NSP Simulated paths, $NTS Time Steps"
	
	cd $BINDIR
	$BINDIR/$PROG $S0 $K $RFR $DIV $SIG $V $THETA $T $NSP $NTS

done
