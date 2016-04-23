#!/bin/ksh
BASEDIR=/home/tjisana/MATH4074/CS1


YEAR=`/bin/date +%Y`
MONTH=`/bin/date +%m`
TODAY=`/bin/date +%d`
HOUR=`/bin/date +%H`
MINUTE=`/bin/date +%M`
#HOUR=16
#MINUTE=20
echo "$HOUR:$MINUTE"

make clean
make
$BASEDIR/bin/CS1.out
