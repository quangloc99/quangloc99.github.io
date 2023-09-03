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
    
    RandomArrayGenerator() = default;
    
    vector<int> generate(int size) {
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
        shuffle(res.begin(), res.end());
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
        return res;
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
    
    // max value for the final array. It is needed for value padding
    int max_val = get_opt("max-val", gen_a.max_value + gen_b.max_value);
    // the bias parameter to use with rnd.wnext
    int padding_bias = get_opt("padding-bias", 0);
    
    auto lengths = rnd.partition(test_count, sum_n, min_n);
    vector<vector<int>> cases;
    for (int i = 0; i < test_count; ++i) {
        int n = lengths[i];
        bool is_yes_test = i < yes_count;
        auto a = gen_a.generate(n);
        auto b = gen_b.generate(n);
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
