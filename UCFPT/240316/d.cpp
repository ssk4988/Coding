#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pi = pair<int, int>;
using pl = pair<ll, ll>;
using pd = pair<ld, ld>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vpi = vector<pi>;
using vpl = vector<pl>;
using vpd = vector<pd>;
using vvi = vector<vi>;

#define f first
#define s second
#define mp make_pair
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define nL "\n"

const ll MOD = 1e9 + 7;
inline ll mod(ll k){
    return k % MOD;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int tot = 0;
    int n, k, t; cin >> n >> k >> t;
    set<vi> s;
    auto dfs = [&](vi &cur, int last, int left, auto &&dfs) -> void {
        if(left == 0){
            s.insert(cur);
            return;
        }
        rep(i, last, left + 1){
            cur.pb(i);
            dfs(cur, i, left - i, dfs);
            cur.pop_back();
        }
    };
    vi cur;
    dfs(cur, 1, n, dfs);
    // cout << n << " " << sz(s) << "\n";
    // tot += sz(s);
    vvi pos;

    for(const vi &cur : s){
        pos.pb(cur);
    }
    int c = sz(s);
    vector<vpi> adj(c);
    rep(u, 0, c){
        const vi &cur = pos[u];
    // }
    // for(const vi &cur : pos){
        vpi freq;
        for(int i : cur){
            if(sz(freq) == 0 || i != freq.back().f){
                freq.push_back({i, 0});
            }
            freq.back().s++;
        }
        for(auto [key, val] : freq){
            rep(i, 1, key){
                if(i > key - i) continue;
                vi cur2(cur);
                cur2.erase(find(all(cur2), key));
                cur2.pb(i);
                cur2.pb(key - i);
                sort(all(cur2));
                int v = lower_bound(all(pos), cur2) - pos.begin();
                adj[u].push_back({v, val * (key / (i == key - i ? 2 : 1))});
                assert(v != sz(pos));
            }
            for(auto [key1, val1] : freq){
                if(key1 > key) break;
                if(key1 == key && val <= 1) continue;
                vi cur2(cur);
                cur2.erase(find(all(cur2), key));
                cur2.erase(find(all(cur2), key1));
                cur2.pb(key + key1);
                sort(all(cur2));
                int v = lower_bound(all(pos), cur2) - pos.begin();
                adj[u].push_back({v, key1 == key ? val * (val - 1) / 2 * key * key : val * val1 * key * key1});
            }
        }
        tot += sz(adj[u]);
    }
    vi init(n, 1);
    int start = lower_bound(all(pos), init) - pos.begin();
    // cout << start << "\n";
    // cout << tot << "\n";
    
    vector<vl> dp(k + 1, vl(c));
    dp[0][0] = 1;
    rep(i, 0, k){
        rep(j, 0, c){
            for(auto [v, m] : adj[j]){
                dp[i+1][j] = mod(dp[i + 1][j] + mod(m * dp[i][v]));
            }
        }
    }
    rep(_, 0, t){
        vi p(n);
        rep(i, 0, n){
            cin >> p[i]; p[i]--;
        }
        vi cycles;
        vi vis(n);
        rep(i, 0, n){
            if(vis[i]) continue;
            int cur = i;
            cycles.pb(0);
            while(!vis[cur]){
                vis[cur] = true;
                cycles.back()++;
                cur = p[cur];
            }
        }
        sort(all(cycles));
        int x = lower_bound(all(pos), cycles) - pos.begin();
        cout << dp[k][x] << "\n";
    }
    
    return 0;
}
