#!/bin/ksh

BASEDIR=/mnt/nas/shared/progQuantCompFinance/lecture6/exampleDataStructure

YEAR=`/bin/date +%Y`
MONTH=`/bin/date +%m`
TODAY=`/bin/date +%d`
HOUR=`/bin/date +%H`
MINUTE=`/bin/date +%M`
#HOUR=16
#MINUTE=20
echo "$HOUR:$MINUTE"

BINDIR=$BASEDIR
PROG=example.out

MARKET=UST
SYMBOL=TY
EXCHANGE=CBOT
	
echo "Launch $MARKET for symbol=$SYMBOL"
echo "Year, Month, Day, Hour, Min = $YEAR/$MONTH/$TODAY at $HOUR:$MINUTE ... "
$BINDIR/$PROG $MARKET $SYMBOL $EXCHANGE $HOUR $MINUTE &

