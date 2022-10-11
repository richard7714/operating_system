#!/bin/bash

FOO=FOO

if [ $FOO = "BAR" ]
then
	echo "This is if"
elif [ $FOO = "FOO" ]
then
	echo "This is elif"
else
	echo "This is else"
fi

echo "This is the end"

