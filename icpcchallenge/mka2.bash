#!/bin/bash
rm -rf ./a2tests
mkdir a2tests
for i in {01..10};
do
    ./generator ${i} > ./a2tests/${i}
    
done
