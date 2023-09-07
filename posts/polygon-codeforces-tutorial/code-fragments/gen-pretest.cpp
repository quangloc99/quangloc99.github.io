#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
#define registerGen(argc, argv, rndVer) prepareOpts(argc, argv)
namespace GenV41 {
#include "gen-v4.1.inc"
}
#undef registerGen

template<class MainFunc>
stringstream call_main(const MainFunc& func, const string& args) {
    vector<string> parts;
    // first string is the program name. We can add anything to it.
    parts.push_back("gen");
    stringstream args_ss(args);
    string arg;
    while (args_ss >> arg) {
        parts.push_back(arg);
        clog << arg << endl;
    }
    vector<char*> argv;
    for (auto& s: parts) argv.push_back(s.data());
    int argc = (int)argv.size();
    
    streambuf* old_buf= cout.rdbuf();
    stringstream out;
    cout.rdbuf(out.rdbuf());
    func(argc, argv.data());
    cout.rdbuf(old_buf);
    return move(out);
}

vector<vector<int>> cases;
void gen41(const string& args) {
    auto out = call_main(GenV41::main, args);
    int test_count;
    out >> test_count;
    while (test_count--) {
        vector<int>& cur_case = cases.emplace_back();
        int n; out >> n;
        cur_case.resize(n);
        for (auto& i: cur_case) out >> i;
    }
}

int sum_n_small = 0;
void backtrack_fill_val(vector<int>& arr, int pos, int max_val) {
    if (pos == (int)arr.size()) {
        cases.push_back(arr);
        sum_n_small += (int)arr.size();
        return ;
    }
    for (int i = 1; i <= max_val; ++i) {
        arr[pos] = i;
        backtrack_fill_val(arr, pos + 1, max_val);
    }
}

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    // generate small tests
    for (int len = 1; len <= 4; ++len) {
        vector<int> arr(len);
        backtrack_fill_val(arr, 0, 5);
    }
    
    int rest_cases = 30000 - (int)cases.size();
    int rest_sum_n = 30000 - sum_n_small;
    rest_cases = min(rest_cases, rest_sum_n / 10);
    gen41(
        "-test-count " + to_string(rest_cases) + " " +
        "-sum-n " + to_string(rest_sum_n) +  " " +
        "-min-a 1 -max-a 400000 -min-b 1 -max-b 400000"
    );
    
    cout << cases.size() << endl;
    for (const auto& a_case: cases) {
        cout << a_case.size() << endl;
        println(a_case);
    }
    
    return 0;
}
