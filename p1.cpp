#include <bits/stdc++.h>
using namespace std;

static const int LOG = 20;
int prnt[200005][LOG];
int prnt_Edge[200005];
int dpth[200005];
int e_in[200005], e_out[200005];
vector<pair<int,int>> adj[200005];
int timer;
int N;
void dfs_rt(int root){
    stack<pair<int,int>> st;
    st.push({root,0});
    prnt[root][0] = root;
    dpth[root] = 0;
    prnt_Edge[root] = -1;
    while(!st.empty()){
        int u = st.top().first;
        int e = st.top().second;
        st.pop();
        for(size_t i=0;i<adj[u].size();i++){
            int h = adj[u][i].first;
            int he = adj[u][i].second;
            if(h == e) 
                continue;
            dpth[h] = dpth[u] + 1;
            prnt[h][0] = u;
            prnt_Edge[h] = he;
            st.push({h,u});
        }
    }
}
void dfs_fun(int root){
    timer = 0;
    vector<pair<int,int>> stkk;
    stkk.push_back({root,0});
    while(!stkk.empty()){
        int u = stkk.back().first;
        int &state = stkk.back().second;
        if(state == 0){
           e_in[u] = timer++;
        }
        if(state < (int)adj[u].size()){
            int v = adj[u][state].first;
            int p = prnt[u][0];
            state++;
            if(v == p) 
                continue;
            stkk.push_back({v,0});
        } else {
            e_out[u] = timer;
            stkk.pop_back();
        }
    }
}
int lcA(int a, int b){
    if(dpth[a] < dpth[b]) 
        swap(a,b);
    int diff = dpth[a]-dpth[b];
    for(int k=0;k<LOG;k++){
        if(diff & (1<<k)) a = prnt[a][k];
    }
    if(a == b) 
        return a;
    for(int k=LOG-1;k>=0;k--){
        if(prnt[a][k] != prnt[b][k]){
            a = prnt[a][k];
            b = prnt[b][k];
        }
    }
    return prnt[a][0];
}

inline int dist(int a, int b){
    int c = lcA(a,b);
    return dpth[a] + dpth[b] - 2*dpth[c];
}
inline bool inSub(int u, int v){
    return e_in[u] >= e_in[v] && e_in[u] <= e_out[v];
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T; 
    cin >> T;

    while(T--){
        cin >> N;
        int M = N + 1;

        vector<pair<int,int>> edges(M);
        for(int i=1;i<=N;i++){
            adj[i].clear();
        }

        for(int i=0;i<M;i++){
            cin >> edges[i].first >> edges[i].second;
        }
        vector<int> dsu(N+1);
        for(int i=1;i<=N;i++) dsu[i]=i;

        function<int(int)> fp = [&](int x){
            return dsu[x]==x?x:dsu[x]=fp(dsu[x]);
        };

        vector<int> isTree(M,0);
        vector<int> backEdges;
        for(int i=0;i<M;i++){
            int u = edges[i].first, v = edges[i].second;
            int ru = fp(u), rv = fp(v);
            if(ru != rv){
                dsu[rv] = ru;
                isTree[i] = 1;
                adj[u].push_back({v,i});
                adj[v].push_back({u,i});
            } else {
                backEdges.push_back(i);
            }
        }
        int R = fp(1);
        bool ok = true;
        for(int i=1;i<=N;i++){
            if(fp(i) != R){ ok=false; break; }
        }
        if(!ok){
            cout << 0 << "\n";
            continue;
        }
        if(backEdges.size() != 2){
            cout << 0 << "\n";
            continue;
        }
        dfs_rt(1);
        for(int k=1;k<LOG;k++){
            for(int v=1;v<=N;v++){
                prnt[v][k] = prnt[prnt[v][k-1]][k-1];
            }
        }
        dfs_fun(1);
        static int treeChild[200005];
        for(int i=0;i<M;i++) 
            treeChild[i] = -1;

        for(int v=2; v<=N; v++){
            int eid = prnt_Edge[v];
            if(eid != -1){
                treeChild[eid] = v;
            }
        }

        int be1 = backEdges[0], be2 = backEdges[1];
        int x1 = edges[be1].first, y1 = edges[be1].second;
        int x2 = edges[be2].first, y2 = edges[be2].second;

        int len1 = dist(x1,y1) + 1;
        int len2 = dist(x2,y2) + 1;

        static int cntOn[200005];
        for(int i=0;i<M;i++) cntOn[i]=0;

        for(int i=0;i<M;i++){
            if(!isTree[i]) continue;
            int child = treeChild[i];
            if(child == -1) continue;

            int c = 0;
            if(inSub(x1,child) ^ inSub(y1,child)) c++;
            if(inSub(x2,child) ^ inSub(y2,child)) c++;
            cntOn[i] = c;
        }

        long long anss = 0;

        for(int i=0;i<M;i++){
            if(!isTree[i]){
                if(i == be1) 
                    anss += len2;
                else anss += len1;
            } else {
                int c = cntOn[i];
                int child = treeChild[i];
                if(c == 1){
                    bool inc1 = (inSub(x1,child) ^ inSub(y1,child));
                    if(inc1) 
                        anss += len2;
                    else anss += len1;
                }
                else if(c == 2){
                    int s1,o1,s2,o2;
                    if(inSub(x1,child)){ 
                        s1=x1; o1=y1; 
                    } 
                    else { 
                        s1=y1; o1=x1; 
                    }
                    if(inSub(x2,child)){ s2=x2; o2=y2; } 
                    else { s2=y2; o2=x2; }

                    anss += (long long)dist(s1,s2) + dist(o1,o2) + 2LL;
                }
                else {
                }
            }
        }

        cout << (anss/2) << "\n";
    }
    return 0;
}
