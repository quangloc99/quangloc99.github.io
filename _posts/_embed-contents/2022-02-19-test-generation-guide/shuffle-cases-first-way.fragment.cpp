vector<bool> is_yes_cases(test_count);
fill(is_yes_cases.begin(), is_yes_cases.begin() + yes_count, true);
shuffle(is_yes_cases.begin(), is_yes_cases.end());

for (int i = 0; i < test_count; ++i) {
    bool is_yes_test = is_yes_cases[i];
    // generate and print the test
}
