// this file is used to include all code fragments in order to ensure their 
// correctness when compile

#include "testlib.h"
#include <bits/stdc++.h>

using namespace std;

// an utility function for getting value and falling-back for a default value
// if the key is not presented.
template<class T>
T get_opt(const string& name, const T& def_val) {
    return has_opt(name) ? opt<T>(name) : def_val;
}

namespace random_array_v1 {
    int n, min_a, max_a;
#include "./random-array-v1.fragment.cpp"
}

namespace random_array_v2 {
    int n, min_a, max_a;
#include "./random-array-v2.fragment.cpp"
}

namespace random_array_v3 {
    int n, min_a, max_a;
#include "./random-array-v3.fragment.cpp"
}

namespace random_array_v4 {
    int n, min_a, max_a;
#include "./random-array-v4.fragment.cpp"
}

namespace random_array_v5 {
    int n;
#include "./random-array-v5.fragment.cpp"
}

namespace random_array_v6 {
    int n;
#include "./random-array-v6.fragment.cpp"
}

namespace adjustment_for_no_tests {
#include "./adjust-random-array-generator-for-no-tests.fragment.cpp"
    int test_count;
    int sum_n;
    int min_n ;
    
    int yes_percent;
    int yes_count;
    
    bool no_shuffle_cases;
    int padding_bias;
    vector<int> lengths;
    vector<vector<int>> cases;
#include "adjust-main-for-no-tests.fragment.cpp"
}


int main() {
    // nothing
}
