template<class MainFunc>
stringstream call_main(const MainFunc& func, const string& args) {
    vector<string> parts;
    // first string is the program name. We can add anything to it.
    parts.push_back("gen");
    stringstream args_ss(args);
    string arg;
    while (args_ss >> arg) {
        parts.push_back(arg);
        clog << arg << endl;
    }
    vector<char*> argv;
    for (auto& s: parts) argv.push_back(s.data());
    int argc = (int)argv.size();
    
    streambuf* old_buf= cout.rdbuf();
    stringstream out;
    cout.rdbuf(out.rdbuf());
    func(argc, argv.data());
    cout.rdbuf(old_buf);
    return move(out);
}

void usage() {
    auto cur = call_main(GenV41::main, "-test-count 1 -sum-n 10 -min-a 1 -max-a 10 -min-b 1 -max-b 10");
    int testcount;
    cur >> testcount;
    // ...
}
