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

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m, k; cin >> n >> m >> k;
    vector<string> pat(n);
    map<string, int> rev;
    rep(i, 0, n){
        cin >> pat[i];
        rev[pat[i]] = i;
    }
    auto matches = [&](string &a, string &b) -> bool {
        rep(i, 0, k){
            if(a[i] == '_' || b[i] == '_' || a[i] == b[i]);
            else return false;
        }
        return true;
    };
    vvi adj(n);
    rep(i, 0, m){
        string str; cin >> str;
        int t; cin >> t; t--;
        if(!matches(str, pat[t])){
            cout << "NO\n";
            return 0;
        }
        rep(j, 0, 1 << k){
            string mask;
            rep(l, 0, k){
                if(j & (1 << l)){
                    mask += '_';
                }
                else mask += str[l];
            }
            if(mask == pat[t] || !rev.count(mask)) continue;
            adj[t].pb(rev[mask]);
            // cout << "edge from " << t << " to " << rev[mask] << endl;
        }
    }
    vi ts;
    bool works = true;
    vi t(n);
    auto dfs = [&](int u, auto &&dfs) -> void {
        if(t[u] == 2) return;
        if(t[u] == 1){
            works = false;
            return;
        }
        t[u] = 1;
        for(int v : adj[u]){
            dfs(v, dfs);
            if(!works) return;
        }
        ts.pb(u);
        t[u] = 2;
    };
    rep(i, 0, n){
        dfs(i, dfs);
    }
    if(!works){
        cout << "NO\n";
    }
    else{
        cout << "YES\n";
        reverse(all(ts));
        for(int i : ts) cout << (i + 1) << " ";
        cout << "\n";
    }
    return 0;
}
