#include <bits/stdc++.h>
using namespace std;

set<vector<int>> visited;
bool solve(vector<int> a) {
    bool all_0 = true;
    for (auto i: a) {
        if (i < 0) return false;
        if (i) all_0 = false;
    }
    if (all_0) return true;
    if (visited.count(a)) return false;
    visited.insert(a);
    // decrease the prefix
    for (auto& i: a) {
        --i;
        if (solve(a)) return true;
    }
    for (auto& i: a) ++i;
    // decrease the suffix
    for (int i = (int)a.size(); i--; ) {
        a[i] --;
        if (solve(a)) return true;
    }
    return false;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int ntest; cin >> ntest;
    while (ntest--) {
        int n; cin >> n;
        vector<int> a(n);
        for (auto& i: a) cin >> i;
        visited.clear();
        cout << (solve(a) ? "YES" : "NO") << '\n';
    }
    return 0;
}
