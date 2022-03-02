./gen-v2 -test-count 10 -yes-percent 30 -no-shuffle-cases -sum-n 100 -min-n 8 -min-a 1 -max-a 100 -min-b 1 -max-b 100 -padding-bias -30 > test.txt
cat test.txt
./solution < test.txt
