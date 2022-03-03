./gen-v4 -no-shuffle-cases -test-count 6 -sum-n 600 -min-n 100 -yes-percent 50 -max-val 30000      -min-a 1 -max-a 1000 -min-b 1 -max-b 1000 > test.txt
./solution < test.txt
python3 plot-test.py test.txt gen-v4-test-for-chaotic-yes-tests.png
