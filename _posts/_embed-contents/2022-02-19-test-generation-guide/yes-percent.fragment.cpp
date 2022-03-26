int yes_percent = has_opt("yes-percent") ? opt<int>("yes-percent") : 50;
int yes_count = test_count * yes_percent / 100;
