#!/usr/bin/env zsh

for file in gcc-mac-x64/*.run; do 
	seed=0x`echo $file | sed 's/.*\/\(.*\)\.run/\1/g'`
	diff -q $file <(../starform -s$seed) && echo 'pass'
done
