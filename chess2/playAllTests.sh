#! /bin/sh
# chmod +x playAllTests.sh

echo "" > allTestsOutput.txt
echo "" > leakCount.txt

for i in testCases/*
do 
    $exec leaks --atExit -- ./Play < $i > allTestsOutput.txt 2> /dev/null
    cat allTestsOutput.txt | grep "total leaked bytes"  > leakCount.txt
    [ -s leakCount.txt ] || echo "ERROR"
    echo "in" $i >> leakCount.txt
    echo "" >> leakCount.txt
    cat leakCount.txt
    rm -r allTestsOutput.txt
done
