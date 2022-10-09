#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& i: a) cin >> i;
    
    auto min_elm = *min_element(a.begin(), a.end());
    auto max_elm = *max_element(a.begin(), a.end());
    for (auto i: a) {
        if (i - min_elm > max_elm - i) cout << min_elm << ' ';
        else cout << max_elm << ' ';
    }
    
    return 0;
}
