#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int tc;
    cin >> tc;
    while (tc--) {
        long long l, r;
        cin >> l >> r;

        long long d = l ^ r; 

        if (d == 0) {
            cout << 0 << "\n"; 
            continue;
        }
        int k = 63 - __builtin_clzll(d);

        long long ans = (1LL << k) - 1;
        cout << ans << "\n";
    }
}
