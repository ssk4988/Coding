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

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n; cin >> n;
        vvi adj(n);
        rep(i, 0, n-1){
            int u, v; cin >> u >> v; u--, v--;
            adj[u].pb(v);
            adj[v].pb(u);
        }
        string str; cin >> str;
        vi cnt(3);
        int other = 0;
        auto dfs = [&](int u, int p, auto &&dfs) -> void {
            int c = 0;
            for(int v : adj[u]){
                if(v == p) continue;
                c++;
                dfs(v, u, dfs);
            }
            if(u != 0 && c == 0){
                if(str[u]!='?') cnt[str[u] - '0']++;
                else cnt[2]++;
            }
            if(u != 0 && c && str[u] == '?') other++;
        };
        dfs(0, -1, dfs);
        int root = str[0] == '?' ? 2 : str[0] - '0';
        int turn = 0;
        while(cnt[2] || root == 2) {
            if(root != 2) {
                if(turn == 0){
                    cnt[1-root]++;
                } else cnt[root]++;
                cnt[2]--;
            }
            else if (max(cnt[0], cnt[1]) > min(cnt[0], cnt[1])){
                if(turn == 0)
                    root = cnt[0] > cnt[1] ? 1 : 0;
                else root = cnt[0] > cnt[1] ? 0 : 1;
            } else {
                if(other) other--;
                else root = 0;
            }
            turn = 1 - turn;
        }
        // if(root == 2) {
        //     root = cnt[0] > cnt[1] ? 1 : 0;
        //     turn = 1;
        // }
        // while(cnt[2]){
        // }
        cout << cnt[1-root] << "\n";
    }
    
    return 0;
}
