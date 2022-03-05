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

void somewhere_inside_main() {
    // ...
    auto gen_a = RandomArrayGenerator::from_opt("a");
    auto gen_b = RandomArrayGenerator::from_opt("b");
    
    // max and min value for the final array. It is needed for value padding
    int max_val = get_opt("max-val", gen_a.max_value + gen_b.max_value);
    int min_val = get_opt("min-val", 1);
    
    // ...
    
    for (int i = 0; i < test_count; ++i) {
        int n = lengths[i];
        bool is_yes_test = i < yes_count;
        auto a = gen_a.generate(n);
        auto b = gen_b.generate(n);
        reverse(b.begin(), b.end());    // reverse here since we no longer 
                                        // sort it decreasingly
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
        int padding = rnd.wnext(min_padding, max_padding, padding_bias);
        for (auto& i: v) i += padding;
        
        cases.push_back(v);
    }
    
    // ...
}


