#!/bin/bash
make solution
rm -rf ./a2
mkdir a2
rm a2.txt
touch a2.txt
for i in {01..05};
do
    ./solution < ./a2tests/${i} > ./a2/${i}.out 2>> a2.txt
done
cat a2.txt
score=$(paste -sd+ a2.txt | bc)
echo "${score}"
