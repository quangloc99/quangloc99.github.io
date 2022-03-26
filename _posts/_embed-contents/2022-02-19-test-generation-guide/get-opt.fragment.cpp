template<class T>
int get_opt(const string& name, const T& default_val) {
    return has_opt(name) ? opt<T>(name) : default_val;
}
// ...
int yes_percent = get_opt("yes-percent", 50);
int yes_count = test_count * yes_percent / 100;
