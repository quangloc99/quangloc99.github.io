struct RandomArrayGenerator {
    int min_value, max_value, value_bias;
    int value_count, picking_bias;
    int noise_percent;
    bool do_sort;   // <---------- new property
    
    RandomArrayGenerator() = default;
    
    vector<int> generate(int size) {
        // ...
        vector<int> res; 
        // ...
        if (do_sort) {
            sort(res.begin(), res.end());
        } else {
            shuffle(res.begin(), res.end());
        }
        return res;
    }
    
    static RandomArrayGenerator from_opt(const string& name) {
        RandomArrayGenerator res;
        // ...
        res.do_sort = get_opt(name + "-sorted", false);
        return res;
    }
};

