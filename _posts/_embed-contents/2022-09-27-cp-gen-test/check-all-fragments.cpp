// This file is for checking all the fragments are compiled.
#include <bits/stdc++.h>

namespace mt19937_examples {
#include "./mt19937-examples.fragment.cpp"
}

namespace macro_examples {
    using namespace std;
#include "./macro-example.fragment.cpp"
}

namespace system_examples {
#include "./system-example.fragment.cpp"
}

int main() {
    using namespace std;
    cout << "NICE" << endl;
}
