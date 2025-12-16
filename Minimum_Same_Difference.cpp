#include <bits/stdc++.h>
using namespace std;
using int64 = long long;
const int MOD = 998244353;

int64 modpow(int64 h, int64 e){
    int64 anss = 1 % MOD;
    h %= MOD;
    while(e){
        if (e & 1) 
            anss = anss * h % MOD;
        h = h * h % MOD;
        e >>= 1;
    }
    return anss;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tc;
    if (!(cin >> tc)) 
        return 0;
    vector<pair<int,int>> hh;
    int mx_K = 0, mx_N = 0;
    hh.reserve(tc);
    for (int i = 0; i < tc;i++){
        int N,K; 
        cin >> N >> K;
        hh.emplace_back(N,K);
        mx_K = max(mx_K, K);
        mx_N = max(mx_N, N);
    }

    int MAX = mx_K; 
    if (MAX < 0) 
        MAX = 0;
    vector<int64> HE(MAX+1,1), HEE(MAX+1,1);
    for (int i = 1; i <= MAX; ++i) 
        HE[i] = HE[i-1] * i % MOD;
    if (MAX >= 1) 
        HEE[MAX] = modpow(HE[MAX], MOD-2);
    for (int i = MAX; i > 0; --i) 
        HEE[i-1] = HEE[i] * i % MOD;
    auto perm = [&](int K, int r)->int64 {
        if (r > K) 
            return 0;
        return HE[K] * HEE[K-r] % MOD;
    };

    for (auto &ehh : hh){
        int N = ehh.first;
        int K = ehh.second;
        int64 ress = 0;
        if (N <= 1) {
            cout << 0 << "\n";
            continue;
        }
        for (int j = 1; j <= N-1;j++){
            int64 ss = 0;
            if (j<= K) {
                if (N <= j) {
                    ss= perm(K, N);
                } else {
                    int64 l = perm(K, j);
                    int64 hee = modpow((K-(j-1)+ MOD) % MOD,N-j);
                    ss = l * hee % MOD;
                }
            } else {
                ss = 0;
            }
            int64 cnt = 0;
            int L = j+1;
            if (L <= K) {
                if (N <= L) {
                    cnt = perm(K, N);
                } else {
                    int64 l = perm(K, L);
                    int64 hee = modpow((K - (L-1) + MOD) % MOD, N - L);
                    cnt = l * hee % MOD;
                }
            } else {
                cnt = 0;
            }

            int64 Cd = (ss -cnt) % MOD;
            if (Cd < 0) Cd += MOD;
            ress = (ress + Cd * j) % MOD;
        }

        cout << ress % MOD << "\n";
    }

    return 0;
}

