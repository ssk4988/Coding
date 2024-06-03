#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vii = vector<pii>;
using vll = vector<pll>;;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

int best_path(int N, int K, int H[][2], int L[]){
    vector<vii> adj(N);
    rep(i, 0, N-1){
        adj[H[i][0]].emplace_back(H[i][1], L[i]);
        adj[H[i][1]].emplace_back(H[i][0], L[i]);
    }
    vector<unordered_map<ll, int>> best(N);
    vl lzw(N); vi lzc(N);
    int ans = INT_MAX;
    auto dfs = [&](int u, int p, auto &&dfs) -> void {
        // cout << "dfs " << u << " " << p << endl;
        best[u][0] = 0;
        int bestc = -1;
        for(auto [v, w] : adj[u]){
            if(v == p) continue;
            dfs(v, u, dfs);
            lzw[v] += w;
            lzc[v]++;
            if(bestc == -1 || sz(best[bestc]) < sz(best[v])) bestc = v;
        }
        if(bestc != -1) {
            swap(best[u], best[bestc]);
            swap(lzw[u], lzw[bestc]);
            swap(lzc[u], lzc[bestc]);
            for(auto [v, w] : adj[u]){
                if(v == p) continue;
                for(auto [len, cnt] : best[v]){
                    if(best[u].count(K - lzw[u] - len - lzw[v])){
                        ans = min(ans, best[u][K - lzw[u] - len - lzw[v]] + cnt + lzc[u] + lzc[v]);
                    }
                }
                for(auto [len, cnt] : best[v]){
                    if(len + lzw[v] <= K + 20) {
                        if(!best[u].count(len + lzw[v] - lzw[u])) best[u][len + lzw[v] - lzw[u]] = INT_MAX;
                        best[u][len + lzw[v] - lzw[u]] = min(best[u][len + lzw[v] - lzw[u]], cnt + lzc[v] - lzc[u]);
                    }
                }
            }
        }
        if(best[u].count(K - lzw[u])) ans = min(ans, best[u][K - lzw[u]] + lzc[u]);
    };
    dfs(0, -1, dfs);
    if(ans == INT_MAX) ans = -1;
    return ans;
}

// int N = 3;
// int K = 3;
// int H[][2] = {{0, 1}, {1, 2}};
// int L[] = {1, 1};

// int N = 4;
// int K = 3;
// int H[][2] = {{0, 1}, {1, 2}, {1, 3}};
// int L[] = {1, 2, 4};

// int N = 11;
// int K = 12;
// int H[][2] = {{0, 1}, {0, 2}, {2, 3}, {3, 4}, {4, 5}, {0, 6}, {6, 7}, {6, 8}, {8, 9}, {8, 10}};
// int L[] = {3, 4, 5, 4, 6, 3, 2, 5, 6, 7};

// int main()
// {
//     cin.tie(0)->sync_with_stdio(0);
//     cin.exceptions(cin.failbit);
//     cout << best_path(N, K, H, L) << "\n";
    
//     return 0;
// }
