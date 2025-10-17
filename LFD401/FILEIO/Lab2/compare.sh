#!/bin/bash

defaultFile=/etc/passwd
[ $# -gt 0 ] && defaultFile=$1


option=$2
if [ "$option" = "remove" ]
then
	rm ./read_hex_offset_stdio
	rm ../Lab1/read_hex
	rm ../Lab1/read_hex_offset
	rm *.out
elif [ "$option" = "build" ]
then
	gcc -O2 -Wall -o ./read_hex_offset_stdio ./read_hex_offset_stdio.c
	gcc -O2 -Wall -o ../Lab1/read_hex ../Lab1/read_hex.c
	gcc -O2 -Wall -o ../Lab1/read_hex_offset ../Lab1/read_hex_offset.c
fi
if [ "$option" = "build" ]
then
	./read_hex_offset_stdio "$defaultFile" > stdio.out
	../Lab1/read_hex "$defaultFile" > read_hex.out
	../Lab1/read_hex_offset "$defaultFile" > read_hex_offset.out
	hexdump -C "$defaultFile" > hexdump.out

	ls -l *out
	wc *out
fi
