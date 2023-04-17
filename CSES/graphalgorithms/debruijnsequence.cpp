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

string binstr(int i, int siz){
    string res;
    for(int j = siz - 1; j >= 0; j--){
        res += (i & (1 << j)) > 0 ? '1' : '0';
    }
    return res;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    int bs = n;
    n = 1 << bs;
    vector<vi> adj(n);
    rep(i, 0, n){
        adj[i].pb(((i & ((1 << (bs - 1)) - 1)) << 1));
        adj[i].pb(((i & ((1 << (bs - 1)) - 1)) << 1) ^ 1);
    }
    bool found = false;
    string sol;
    string ans;
    auto dfs = [&](vi &used, int last, int cnt, auto &&dfs)->void{
        if(found) return;
        used[last] = true;
        if(cnt == n){
            // cout << binstr(bits, bs + n - 1) << nL;
            found = true;
            ans = sol;
            return;
        }

        rep(i, 0, 2){
            if(used[adj[last][i]])continue;
            // if(adj[last][i] == 0) cout << "bruh" << nL;
            sol += i ? '1' : '0';
            dfs(used, adj[last][i], cnt + 1, dfs);
            sol.pop_back();
        }
        used[last] = false;
    };
    vi used(n);
    rep(i, 0, n){
        sol = binstr(i, bs);
        dfs(used, i, 1, dfs);
        // break;
    }
    cout << ans << nL;
    // rep(i, 0, sz(sol) - bs){
    //     int c = stoi(sol.substr(i, bs), 0, 2);
    //     if(used[c]) cout << c << " is used twice" << nL;
    //     used[c] = true;
    //     // cout <<  << nL;
    // }
    // rep(i, 0, n){
    //     if(!used[i]) cout << i << " is not used" << nL;
    // }
    
    return 0;
}
