#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

// an utility function for getting value and falling-back for a default value
// if the key is not presented.
template<class T>
T get_opt(const string& name, const T& def_val) {
    return has_opt(name) ? opt<T>(name) : def_val;
}

vector<int> random_array(int size, int min_value, int max_value) {
    vector<int> res(size);
    for (auto& i: res) i = rnd.next(min_value, max_value);
    return res;
}

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    
    int test_count = opt<int>("test-count");
    int sum_n = opt<int>("sum-n");
    // minimum length for a test case
    int min_n = get_opt("min-n", 1);
    
    // use percentages for the number of YES tests
    int yes_percent = get_opt("yes-percent", 50);
    int yes_count = test_count * yes_percent / 100;
    
    // add no-shuffle-cases for us to see if the generator works properly.
    bool no_shuffle_cases = opt<bool>("no-shuffle-cases");
    
    // value range for the array a (i.e the increasing array)
    int min_a = opt<int>("min-a");
    int max_a = opt<int>("max-a");
    // value range for the array b (i.e the decreasing array)
    int min_b = opt<int>("min-b");
    int max_b = opt<int>("max-b");
    
    // max value for the final array. It is needed for value padding
    int max_val = get_opt("max-val", max_a + max_b);
    // the bias parameter to use with rnd.wnext
    int padding_bias = get_opt("padding-bias", 0);
    
    auto lengths = rnd.partition(test_count, sum_n, min_n);
    vector<vector<int>> cases;
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
        int max_elm = *max_element(a.begin(), a.end());
        int max_padding = max_val - max_elm;
        int padding = rnd.wnext(0, max_padding, padding_bias);
        for (auto& i: a) i += padding;
        
        cases.push_back(a);
    }
    
    if (!no_shuffle_cases) {
        shuffle(cases.begin(), cases.end());
    }
    
    cout << test_count << '\n';
    for (const auto& a_case: cases) {
        cout << a_case.size() << '\n';
        println(a_case);
    }
    
    return 0;
}
