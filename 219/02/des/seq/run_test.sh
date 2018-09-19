#!/bin/bash

TESTCASE=${1:-des}
FILEIN=${2:-tale_of_two_cities.txt}

AUX=`basename ${FILEIN%.*}`
OUTLOG=log_${TESTCASE}_${AUX}_seq.log

make 
touch ${OUTLOG}
for i in `seq 1 20`; do
	# user time
	utime="$( TIMEFORMAT='%lU';time ( ./${TESTCASE} ${FILEIN} ) 2>&1 1>/dev/null )" 
	echo ${i} ${utime} >> ${OUTLOG} 
	rm -f file.dec file.enc
done

sed 's/0m//g' ${OUTLOG}  | sed 's/s//g' >tmp.log; mv tmp.log ${OUTLOG}

cp ${OUTLOG} ../../logs/.
