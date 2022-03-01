#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    
    // getting the options 
    int test_count = opt<int>("test-count");
    int sum_n = opt<int>("sum-n");
    int min_a = opt<int>("min-a");
    int max_a = opt<int>("max-a");
    
    auto lengths = rnd.partition(test_count, sum_n);
    cout << test_count << '\n';
    for (auto n: lengths) {
        vector<int> a(n);
        for (auto& i: a) {
            i = rnd.next(min_a, max_a);
        }
        cout << n << '\n';
        println(a);     // println will not print additional spaces
                        // at the end of the line
    }
    
    return 0;
}
