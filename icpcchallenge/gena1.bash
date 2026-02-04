#!/bin/bash
make solution
rm -rf ./a1
mkdir a1
rm a1.txt
touch a1.txt
for i in {01..10};
do
    ./solution < ./tests/${i} > ./a1/${i}.out 2>> a1.txt
done
cat a1.txt
score=$(paste -sd+ a1.txt | bc)
echo "${score}"
zip -j a1.zip ./a1/*
