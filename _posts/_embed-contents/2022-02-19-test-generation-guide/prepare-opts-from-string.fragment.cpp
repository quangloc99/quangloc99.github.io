void prepare_opts_from_string(const string& args) {
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
    prepareOpts(argc, argv.data());
}

