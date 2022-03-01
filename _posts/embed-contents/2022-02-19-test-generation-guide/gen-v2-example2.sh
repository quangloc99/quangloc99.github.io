./gen-v2 -test-count 4 -sum-n 45 -min-n 10 -min-a 1 -max-a 100 -min-b 1 -max-b 100 -padding-bias 30 > test.txt
cat test.txt
./solution < test.txt
