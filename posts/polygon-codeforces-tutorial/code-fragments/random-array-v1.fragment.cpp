vector<int> random_array(int size, int min_value, int max_value, int value_count) {
    vector<int> res(size);
    if (value_count > 0) {
        vector<int> values;
        for (int i = 0; i < value_count; ++i) {
            values.push_back(rnd.next(min_value, max_value));
        }
        for (auto& i: res) i = rnd.any(values);
    } else {
        for (auto& i: res) i = rnd.next(min_value, max_value);
    }
    return res;
}
void gen_a_example() {
    auto a = random_array(n, min_a, max_a, get_opt("a-limited-value", 0));
    sort(a.begin(), a.end());
}
