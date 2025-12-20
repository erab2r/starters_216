#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        long long n;
        int k;
        cin >> n >> k;

        if (k == 1) {
            cout << n << "\n";
            continue;
        }

        if (k % 2 == 1) {
            // odd k → all n
            for (int i = 0; i < k; i++) {
                cout << n << " ";
            }
            cout << "\n";
        } else {
            // even k → one 0, rest n
            cout << 0 << " ";
            for (int i = 1; i < k; i++) {
                cout << n << " ";
            }
            cout << "\n";
        }
    }
    return 0;
}
