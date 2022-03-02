struct RandomArrayGenerator {
    int min_value, max_value, value_bias;
    int value_count, picking_bias;
    int noise_percent;  // <--- new property
    
    RandomArrayGenerator() = default;
    
    vector<int> generate(int size) {
        // we still want to use the original gen val function,
        // so let's separate it and give it another name.
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
        
        // the original gen_val function can be used here to generate noise.
        for (int i = 0; i < noise_count; ++i) {
            res.push_back(gen_random_val());
        }
        // we should shuffle the array since we only add noise to the back
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

void gen_a_example() {
    auto generator_for_a = RandomArrayGenerator::from_opt("a");
    auto a = generator_for_a.generate(n);
    sort(a.begin(), a.end());
}
