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
    int nc;
    cin >> nc;
    map<vi, int> rl;
    rep(cn, 0, nc)
    {
        int n;
        cin >> n;
        vvi adj(n);
        rep(i, 0, n - 1)
        {
            int a, b;
            cin >> a >> b;
            a--, b--;
            adj[a].pb(b);
            adj[b].pb(a);
        }
        vi hs(n);
        auto dfs = [&](int cur, int par, auto &&dfs) -> void
        {
            vi cs;
            for (int nex : adj[cur])
            {
                if (nex == par)
                    continue;
                dfs(nex, cur, dfs);
                cs.pb(hs[nex]);
            }
            // devise unique ordering method so that mirrors will have same hashes in both directions 
            sort(all(cs));
            if (rl.count(cs) == 0)
                rl[cs] = sz(rl);
            hs[cur] = rl[cs];
            // unordered_map<int, int> freq;
            // for(int i : cs) freq[i]++;
            // int odd = 0;
            // for(auto [key, fr] : freq){
            //     if(fr % 2 == 1) odd += 1 + !mirror[key];
            // }
            // if(odd <= 1) mirror[hs[cur]] = true;
            
        };
        dfs(0, -1, dfs);
        int hash1 = hs[0];
        adj = vvi(n);
        rep(i, 0, n - 1)
        {
            int a, b;
            cin >> a >> b;
            a--, b--;
            adj[a].pb(b);
            adj[b].pb(a);
        }
        hs = vi(n);
        dfs(0, -1, dfs);
        int hash2 = hs[0];
        cout << (hash1 == hash2 ? "YES" : "NO") << nL;
    }
 
    return 0;
}