#include <bits/stdc++.h>
using namespace std;

mt19937 rng;
int rand(int l, int r) {
    return l + (int)(rng() % (r - l + 1));
}

const int maxn = 101010;
int n;
int a[maxn];
set<int> values;

void gentest(ostream& input) {
    n = rand(1, 10);
    input << n << '\n';
    values.clear();
    for (int i = 0; i < n; ++i) {
        int val = rand(1, 100);
        a[i] = val;
        input << val << ' ';
        values.insert(val);
    }
}

vector<int> read_ans(istream& output) {
    vector<int> distance(n);
    for (int i = 0; i < n; ++i) {
        int num;
        output >> num;
        assert(values.count(num));          // <-- assert here
        distance[i] = abs(num - a[i]);
    }
    return distance;
}

bool check(istream& output1, istream& output2) {
    return read_ans(output1) == read_ans(output2);
}

int main() {
    for (int testcase = 1; testcase <= 1000; ++testcase) {
        ofstream input("main.inp");
        gentest(input);
        input.close();
        
        if (system("./slow-solution < main.inp > slow.out")) {
            cout << "RE slow" << endl;
            exit(0);
        }
        if (system("./fast-solution < main.inp > fast.out")) {
            cout << "RE fast" << endl;
            exit(0);
        }
        
        ifstream slow_output("slow.out");
        ifstream fast_output("fast.out");
        if (!check(slow_output, fast_output)) {
            cout << "WA" << endl;
            exit(0);
        }
        cout << "OK" << endl;
    }
}
