./gen-v2 -test-count 3 -sum-n 40 -min-n 10 -min-a 1 -max-a 100 -min-b 1 -max-b 100 > test.txt
cat test.txt
./solution < test.txt
