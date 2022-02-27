#include "testlib.h"
using namespace std;

const int max_testcount = 30000;
const int max_n = 30000;
const int max_val = (int)1e6;

int main(int argc, char** argv) {
    registerValidation(argc, argv);
    int testcount = inf.readInt(1, max_testcount, "test-count");
    inf.readEoln();
    int sum_n = 0;
    for (int testcase = 1; testcase <= testcount; ++testcase) {
        setTestCase(testcase);
        int n = inf.readInt(1, max_n, "n");
        sum_n += n;
        ensuref(sum_n <= max_n, "sum of n over all cases should not exceed %d", max_n);
        inf.readEoln();
        inf.readInts(n, 1, max_val, "a");
        inf.readEoln();
    }
    inf.readEof();
    return 0;
}
