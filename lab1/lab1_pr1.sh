#!/bin/bash

i=0

while [ $i -lt 50 ]
do
	if [ (($i)%9) -eq 0 ]; then
		echo "Number : $i"
	fi
done

echo 'All Done!'
