## All NO
./gen-v4 -no-shuffle-cases -test-count 6 -sum-n 600 -min-n 100 -yes-percent 0 -max-val 2000 -min-a 1 -max-a 1000 -min-b 1 -max-b 1000 > test.txt
./solution < test.txt
## Ans only 1 YES
## (2>&1 is for redirecting the error message to stdout because I only capture stdout)
./gen-v4 -no-shuffle-cases -test-count 1 -sum-n 100 -min-n 100 -yes-percent 100 -max-val 2000 -min-a 1 -max-a 1000 -min-b 1 -max-b 1000 2>&1 > test.txt
