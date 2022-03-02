./gen-v3 -test-count 5 -sum-n 30000 -min-n 6000 -yes-percent 100 -padding-bias -1000 -min-b 0 -max-b 0    -min-a 1 -max-a 10000 -a-limited-value 10 -a-value-bias 5 -a-picking-bias 5 -a-noise-percent 10 > test.txt
./solution < test.txt
python3 plot-test.py test.txt gen-v3-test-increasing.png
