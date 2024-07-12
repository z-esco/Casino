#!/bin/sh
touch linkList.txt
ls *.o > linkList.txt

CMD="g++ "
while read -r FILE; 
do
    CMD+="$FILE "

done < linkList.txt
CMD+="-o ./playgame"
eval "$CMD"
./playgame
