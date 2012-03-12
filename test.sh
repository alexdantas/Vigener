#!/bin/bash
#	test.sh
#	Simple test script for vigener
#		./test.sh [message] [key]
#	It cryptographs and decryptographs the message with the
#	key, both specified at the command-line.
#	If the output lines are not the same, there's something wrong
#
STRING=$1
KEY=$2

echo $STRING
echo $STRING | ./vigener -e $KEY | ./vigener -d $KEY
echo

