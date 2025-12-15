#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int tc;
    cin >> tc;

    while (tc--) {
        int N;
        cin >> N;
        int anss = 0; 
        for (int i = 1; i <= N; i++) {
            int  e;
            cin >> e;
            if (e == 1) 
                anss++;
        }
        int ress = N - anss / 2;
        cout << ress << "\n";
    }
    return 0;
}