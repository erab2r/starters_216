#include <bits/stdc++.h>
using namespace std;

long long computeScore(const vector<int>& P) {
    int N = P.size();
    long long ans = 0;

    for (int L = 0; L < N; L++) {
        vector<int> freq(N + 1, 0);
        int mex = 0;

        for (int R = L; R < N; R++) {
            freq[P[R]] = 1;
            while (freq[mex]) mex++;
            ans += mex;
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int tc;
    cin >> tc;
    while (tc--) {
        int N;
        cin >> N;
        vector<int> Q(N);

        vector<int> present(N, 0);
        for (int i = 0; i < N; i++) {
            cin >> Q[i];
            if (Q[i] != -1) present[Q[i]] = 1;
        }

        vector<int> missing;
        for (int x = 0; x < N; x++)
            if (!present[x]) missing.push_back(x);

        // Sort missing numbers descending
        sort(missing.rbegin(), missing.rend());
        int idx = 0;
        for (int i = 0; i < N; i++) {
            if (Q[i] == -1) {
                Q[i] = missing[idx++];
            }
        }

        cout << computeScore(Q) << "\n";
    }
    return 0;
}
