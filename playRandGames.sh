#! /bin/sh
# chmod +x playRandGames.sh

cd chess
echo "" > del.txt
make > del.txt
rm -r del.txt
cd ..
echo "" > endOfGames.txt

for i in {1..10}
do 
    $exec ./makeInputs > testFile1.txt
    $exec chess/Play True < testFile1.txt > testFileOut.txt
    tail -n 23 testFileOut.txt >> endOfGames.txt

    echo "" >> endOfGames.txt
    echo "" >> endOfGames.txt
    echo "----- END HERE -----" >> endOfGames.txt
    echo "" >> endOfGames.txt
    echo "" >> endOfGames.txt
    echo "" >> endOfGames.txt
    echo $i
done

rm -r testFileOut.txt
rm -r testFile1.txt
