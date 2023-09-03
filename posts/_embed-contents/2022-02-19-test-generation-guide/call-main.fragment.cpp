template<class MainFunc>
void call_main(const MainFunc& func, const string& args) {
    vector<string> parts;
    // first string is the program name. We can add anything to it.
    parts.push_back("gen");
    stringstream ss(args);
    string arg;
    while (ss >> arg) {
        parts.push_back(arg);
    }
    vector<char*> argv;
    for (auto& s: parts) argv.push_back(s.data());
    int argc = (int)argv.size();
    func(argc, argv.data());
}

void usage() {
    call_main(GenV41::main, "-test-count 1 -sum-n 10 -min-a 1 -max-a 10 -min-b 1 -max-b 10");
}
