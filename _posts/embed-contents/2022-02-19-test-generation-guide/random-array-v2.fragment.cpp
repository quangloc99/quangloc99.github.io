vector<int> random_array(int size, int min_value, int max_value, int value_count) {
    function<int()> gen_val = [&]() {
        return rnd.next(min_value, max_value);
    };
    if (value_count > 0) {
        vector<int> values;
        for (int i = 0; i < value_count; ++i) {
            values.push_back(gen_val());
        }
        gen_val = [values]() { return rnd.any(values); };
    }
    vector<int> res(size);
    for (auto& i: res) i = gen_val();
    return res;
}

void gen_a_example() {
    auto a = random_array(n, min_a, max_a, get_opt("a-limited-value", 0));
    sort(a.begin(), a.end());
}
