./gen-v1 -test-count 5 -sum-n 50 -yes-count 2 -min-a 1 -max-a 100 -min-b 1 -max-b 100 > test.txt
cat test.txt
./solution < test.txt
