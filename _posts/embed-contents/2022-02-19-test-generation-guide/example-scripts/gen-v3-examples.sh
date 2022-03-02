./gen-v3 -test-count 5 -sum-n 30000 -min-n 6000 -yes-percent 100 -padding-bias -1000    -min-a 1 -max-a 10000 -a-limited-value 10 -a-value-bias 5 -a-picking-bias 5 -a-noise-percent 10    -min-b 1 -max-b 10000 -b-limited-value 20 -b-picking-bias 5 -b-noise-percent 50 > test.txt
python3 plot-test.py test.txt gen-v3-example1.png

./gen-v3 -test-count 5 -sum-n 30000 -min-n 6000 -yes-percent 100 -padding-bias -1000    -min-a 1 -max-a 10000 -a-limited-value 10 -a-value-bias 5 -a-picking-bias 5 -a-noise-percent 10    -min-b 1 -max-b 10000 -b-limited-value 10 -b-picking-bias 0 -b-noise-percent 10 > test.txt
python3 plot-test.py test.txt gen-v3-example2.png

./gen-v3 -test-count 5 -sum-n 30000 -min-n 6000 -yes-percent 100 -padding-bias -1000    -min-a 1 -max-a 10000 -a-limited-value 10 -a-value-bias 5 -a-picking-bias 5 -a-noise-percent 10    -min-b 1 -max-b 10000 -b-limited-value 10 -b-picking-bias -5 -b-noise-percent 10 > test.txt
python3 plot-test.py test.txt gen-v3-example3.png
