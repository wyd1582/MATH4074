#!/bin/ksh
BASEDIR=/home/tjisana/MATH4074/CS4


YEAR=`/bin/date +%Y`
MONTH=`/bin/date +%m`
TODAY=`/bin/date +%d`
HOUR=`/bin/date +%H`
MINUTE=`/bin/date +%M`
PROG=CS4.out
FILE=Parameters.txt
#HOUR=16
#MINUTE=20
echo "$HOUR:$MINUTE"

make clean
make
$BASEDIR/bin/$PROG $FILE
