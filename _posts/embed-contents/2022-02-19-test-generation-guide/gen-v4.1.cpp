#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

// an utility function for getting value and falling-back for a default value
// if the key is not presented.
template<class T>
T get_opt(const string& name, const T& def_val) {
    return has_opt(name) ? opt<T>(name) : def_val;
}

struct RandomArrayGenerator {
    int min_value, max_value, value_bias;
    int value_count, picking_bias;
    int noise_percent;
    bool do_sort_in_no_test;
    
    RandomArrayGenerator() = default;
    
    vector<int> generate(int size, bool for_yes_test) {
        function<int()> gen_random_val = [&]() {
            return rnd.wnext(min_value, max_value, value_bias);
        };
        auto gen_val = gen_random_val;
        if (value_count > 0) {
            vector<int> values;
            for (int i = 0; i < value_count; ++i) {
                values.push_back(gen_val());
            }
            gen_val = [=]() {
                return values[rnd.wnext(values.size(), picking_bias)];
            };
        }
        int noise_count = size * noise_percent / 100;
        vector<int> res(size - noise_count);
        for (auto& i: res) i = gen_val();
        
        for (int i = 0; i < noise_count; ++i) {
            res.push_back(gen_random_val());
        }
        if (for_yes_test or do_sort_in_no_test) {
            sort(res.begin(), res.end());
        } else {
            shuffle(res.begin(), res.end());
        }
        return res;
    }
    
    static RandomArrayGenerator from_opt(const string& name) {
        RandomArrayGenerator res;
        res.min_value = opt<int>("min-" + name);
        res.max_value = opt<int>("max-" + name);
        res.value_bias = get_opt(name + "-value-bias", 0);
        res.value_count = get_opt(name + "-limited-value", 0);
        res.picking_bias = get_opt(name + "-picking-bias", 0);
        res.noise_percent = get_opt(name + "-noise-percent", 0);
        res.do_sort_in_no_test = get_opt(name + "-sorted-in-no", false);
        return res;
    }
};

// a solver that solve the input but does not care about number being negative.
struct Solver {
    vector<int> inc, dec;
    Solver(const vector<int>& a): inc(a.size()), dec(a.size()) {
        dec[0] = a[0];
        for (int i = 1; i < (int)a.size(); ++i) {
            dec[i] = min(dec[i - 1], a[i] - inc[i - 1]);
            inc[i] = a[i] - dec[i];
        }
    }
};

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
    
    auto gen_a = RandomArrayGenerator::from_opt("a");
    auto gen_b = RandomArrayGenerator::from_opt("b");
    
    // max and min value for the final array. It is needed for value padding
    int max_val = get_opt("max-val", gen_a.max_value + gen_b.max_value);
    int min_val = get_opt("min-val", 1);
    // the bias parameter to use with rnd.wnext
    int padding_bias = get_opt("padding-bias", 0);
    
    auto lengths = rnd.partition(test_count, sum_n, min_n);
    vector<vector<int>> cases;
    for (int i = 0; i < test_count; ++i) {
        int n = lengths[i];
        bool is_yes_test = i < yes_count;
        auto a = gen_a.generate(n, is_yes_test);
        auto b = gen_b.generate(n, is_yes_test);
        reverse(b.begin(), b.end());
        vector<int> v(n);
        for (int i = 0; i < n; ++i) v[i] = a[i] + b[i];
        
        Solver optimal(v);
        
        // Calculate the padding. Note that padding can be negative.
        auto [min_elm, max_elm] = minmax_element(v.begin(), v.end());
        int max_padding = max_val - *max_elm;
        int min_padding = min_val - *min_elm;
        
        int min_dec = *min_element(optimal.dec.begin(), optimal.dec.end());
        if (is_yes_test) {
            min_padding = max(min_padding, -min_dec);
        } else {
            max_padding = min(max_padding, -min_dec - 1);
        }
        
        // side question: what if min_dec > maxdec?
        ensuref(min_padding <= max_padding, "min_padding must not exceed max_padding, but found min_padding = %d, max_padding = %d", min_padding, max_padding);
        int padding = rnd.wnext(min_padding, max_padding, padding_bias);
        for (auto& i: v) i += padding;
        
        cases.push_back(v);
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

