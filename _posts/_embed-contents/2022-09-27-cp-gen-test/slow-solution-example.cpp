#include <iostream>
#include <vector>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& value: a) cin >> value;
    
    for (auto value: a) {
        int ans = value;
        for (auto other: a) {
            if (abs(ans - value) < abs(ans - other)) {
                ans = other;
            }
        }
        cout << ans << ' ';
    }
}
