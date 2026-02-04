#!/bin/bash
cat a1.txt
score=$(paste -sd+ a1.txt | bc)
echo "${score}"
