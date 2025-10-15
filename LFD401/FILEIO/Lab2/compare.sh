#!/bin/bash

defaultFile=/etc/passwd
[ $# -gt 0 ] && defaultFile=$1

./read_hex_offset_stdio "defaultFile" > stdio.out
../
