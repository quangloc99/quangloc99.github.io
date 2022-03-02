struct RandomArrayGenerator {
    int min_value, max_value, value_bias;
    int value_count, picking_bias;
    
    RandomArrayGenerator() = default;
    
    vector<int> generate(int size) {
        function<int()> gen_val = [&]() {
            return rnd.wnext(min_value, max_value, value_bias);
        };
        if (value_count > 0) {
            vector<int> values;
            for (int i = 0; i < value_count; ++i) {
                values.push_back(gen_val());
            }
            gen_val = [=]() {
                return values[rnd.wnext(values.size(), picking_bias)];
            };
        }
        vector<int> res(size);
        for (auto& i: res) i = gen_val();
        return res;
    }
    
    static RandomArrayGenerator from_opt(const string& name) {
        RandomArrayGenerator res;
        res.min_value = opt<int>("min-" + name);
        res.max_value = opt<int>("max-" + name);
        res.value_bias = get_opt(name + "-value-bias", 0);
        res.value_count = get_opt(name + "-limited-value", 0);
        res.picking_bias = get_opt(name + "-picking-bias", 0);
        return res;
    }
};

void gen_a_example() {
    auto generator_for_a = RandomArrayGenerator::from_opt("a");
    auto a = generator_for_a.generate(n);
    sort(a.begin(), a.end());
}
