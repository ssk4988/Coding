
g++ -O2 -o gen gen.cpp
javac c.java
g++ -O2 -o brute brute.cpp

while [ 1 -eq 1 ]
do
    gen > test.in
    java c < test.in > test.wrong
    brute < test.in > test.ans
    diff test.wrong test.ans
    if [$? -ne 0]
    then
        exit
    fi
done