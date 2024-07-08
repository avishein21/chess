#! /bin/sh
# chmod +x makeLegalGame.sh
echo "" > legalIn.txt
echo "" > testFileOut1.txt
echo "" > testFileOut2.txt

$exec ./makeInputs > testFile1.txt

oldSize=$(wc -c <"testFileOut1.txt")
while read line
do 
cp legalIn.txt legalInTest.txt
echo $line >> legalInTest.txt
echo Quit >> legalInTest.txt
$exec chess/Play True < legalInTest.txt > testFileOut1.txt
newSize=$(wc -c <"testFileOut1.txt")
if [ $newSize != $oldSize ]
then 
    echo $line >> legalIn.txt
fi
oldSize=$newSize
tag=$( tail -12 testFileOut1.txt | head -1)
wordList=($tag)
if [ ${wordList[0]} == "Game" ]
then
    break
fi
done < testFile1.txt
echo Quit >> legalIn.txt
##check for game over
