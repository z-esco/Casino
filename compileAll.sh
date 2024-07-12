#!/bin/sh
touch compileList.txt
ls *.cpp > compileList.txt

while read -r FILE;
do 
  g++ -c $FILE
done <  compileList.txt