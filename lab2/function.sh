#!/bin/sh

add_a_user()
{
	USER=$1
	PASSWORD=$2

	echo "Adding user $USER  ..."
	echo useradd $USER
	echo passwd $USER $PASSWORD
	echo "Added user $USER with pass $PASSWORD"
}

echo "Start of script..."
add_a_user ma ma
echo "End of script..."
