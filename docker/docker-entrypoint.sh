#!/bin/ash

JSON=/opt/data/corpus.json
SRC=${JSON}.gz
DAT=/opt/data/corpus.dat

if [ -n "$CREDENTIALS" ]
then
    if [ -f $SRC ]
    then
        find $SRC -mtime $MAXAGE -exec curl -L -u $CREDENTIALS -o {} 'http://datafeeds.networkrail.co.uk/ntrod/SupportingFileAuthenticate?type=CORPUS' \;
    else
        curl -L -u $CREDENTIALS -o $SRC 'http://datafeeds.networkrail.co.uk/ntrod/SupportingFileAuthenticate?type=CORPUS'
    fi
fi

if [ -f $DAT -a -f $SRC -a $SRC -nt $DAT ]
then
    rm -f $DAT
fi

if [ ! -f $DAT ]
then
    if [ -f $SRC ]
    then
        gunzip <$SRC >$JSON
        corpus-import $JSON $DAT
        rm -f $JSON
    else
        echo "No data file available"
        exit
    fi
fi

exec corpusd -p$PORT -ip4 -ip6 $DAT
