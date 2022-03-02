vector<int> random_array(
    int size,
    int min_value, int max_value, int value_bias,
    int value_count, int picking_bias
) {
    function<int()> gen_val = [&]() {
        return rnd.wnext(min_value, max_value, value_bias);
    };
    if (value_count > 0) {
        vector<int> values;
        for (int i = 0; i < value_count; ++i) {
            values.push_back(gen_val());
        }
        gen_val = [values, picking_bias]() {
            //////////////// use picking-bias here
            return values[rnd.wnext(values.size(), picking_bias)];
        };
    }
    vector<int> res(size);
    for (auto& i: res) i = gen_val();
    return res;
}

void gen_a_example() {
    auto a = random_array(
        n, min_a, max_a, get_opt("a-value-bias", 0),
        get_opt("a-limited-value", 0),
        get_opt("a-picking-bias", 0)
    );
    sort(a.begin(), a.end());
}
