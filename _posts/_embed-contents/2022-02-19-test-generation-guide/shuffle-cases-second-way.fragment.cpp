using TestCase = vector<int>;
// ...
vector<TestCase> cases;
for (int i = 0; i < test_count; ++i) {
    bool is_yes_test = i < yes_count;  // the old way to determine the test type.
    TestCase the_case;
    // generate the test and store it into the test_case ...
    cases.push_back(the_case);
}
shuffle(cases.begin(), cases.end());
// print the cases
