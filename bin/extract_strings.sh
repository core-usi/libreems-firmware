#!/bin/bash

if [ $# -ne 3 ]; then
	echo "Need filename to process, key to search (name, description) and string prefix"
	exit -1
fi
FILENAME=$1
SEARCH=$2
PREFIX=$3
IFS=$'\n'


for string in $(grep \.${SEARCH} "${FILENAME}" |
	cut -f2 -d\" 
	) ; do 
	VALUE="$string"
	KEY=$(
		echo "${PREFIX}_$string" | 
		tr '[:lower:]' '[:upper:]' |
		tr -d \,\.\)\' |
		tr -s \  \_ |
		tr -s \- \_ |
		tr -s \/ \_ |
		tr -s \( \_
		)
	#echo "Value ${VALUE}"
	#echo "Key ${KEY}"
	echo "const int8_t ${KEY}[] PPAGE_E6 = \"$VALUE\";"
	sed -i -e "s~\"${VALUE}\".*~${KEY},~g" "${FILENAME}"
done
