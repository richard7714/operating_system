#!/bin/bash

echo -n "Enter the name of a country: "
read COUNTRY

echo -n "The official language of $COUNTRY is "

case $COUNTRY in

	Korea)
		echo -e -n "Korean\n"
		;;

	USA | England | Australia | Canada)
		echo -n "English"
		;;

	Brazil | Portugal)
		echo -n "Portuguese"
		;;

	*)
		echo -n "unknown"
		;;
esac
