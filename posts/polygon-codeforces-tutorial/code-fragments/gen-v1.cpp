#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

vector<int> random_array(int size, int min_value, int max_value) {
    vector<int> res(size);
    for (auto& i: res) i = rnd.next(min_value, max_value);
    return res;
}

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    
    // getting the options 
    int test_count = opt<int>("test-count");
    int sum_n = opt<int>("sum-n");
    int yes_count = opt<int>("yes-count");
    // value range for the array a (i.e the increasing array)
    int min_a = opt<int>("min-a");
    int max_a = opt<int>("max-a");
    // value range for the array b (i.e the decreasing array)
    int min_b = opt<int>("min-b");
    int max_b = opt<int>("max-b");
    
    auto lengths = rnd.partition(test_count, sum_n);
    cout << test_count << '\n';
    for (int i = 0; i < test_count; ++i) {
        int n = lengths[i];
        bool is_yes_test = i < yes_count;
        auto a = random_array(n, min_a, max_a);
        auto b = random_array(n, min_b, max_b);
        if (is_yes_test) {
            sort(a.begin(), a.end());
            sort(b.rbegin(), b.rend());
        }
        for (int i = 0; i < n; ++i) a[i] += b[i];
        cout << n << '\n';
        println(a);
    }
    return 0;
}
