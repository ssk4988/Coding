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
    vi par(n);
    vector<vpi> sub(n), parsub(n);
    map<int, bool> good;
    map<vpi, int> hsh;
    auto calc = [&](vpi &v) -> int {
        if(!hsh.count(v)){
            hsh[v] = sz(hsh);
            bool flag = true;
            for(auto [key, val] : v){
                if(!good[key]) flag = false;
            }
            good[hsh[v]] = flag && sz(v) <= 1;
        }
        return hsh[v];
    };
    auto dfs = [&](int u, int p, auto &&dfs) -> bool
    {
        par[u] = p;
        auto it = find(all(adj[u]), p);
        if (it != adj[u].end())
            adj[u].erase(it);
        map<int, int> freq;
        for (int v : adj[u])
        {
            if (!dfs(v, u, dfs))
                return false;
            freq[hsh[sub[v]]]++;
        }
        if (sz(freq) >= 3)
            return false;
        sub[u] = vpi(all(freq));
        // cout << u << ":\n";
        // for(auto [key, val] : sub[u]){
        //     cout << key << "," << val << "\n";
        // }
        // for(auto [key, val] : freq) sub[u].push_back({key, val});
        calc(sub[u]);
        // cout << u << " " << hsh[sub[u]] << " " << good[hsh[sub[u]]] << "\n";
        return true;
    };
    bool works = dfs(0, -1, dfs);
    if (!works)
    {
        cout << -1 << "\n";
        cerr << "had more than 3 different subtrees somewhere\n";
        return 0;
    }
    int ans = -2;
    auto reroot = [&](int u, auto &&reroot) -> void
    {
        map<int, int> freq(all(sub[u]));
        // for (auto [key, val] : sub[u])
        //     freq[key] = val;
        if (par[u] != -1)
        {
            map<int, int> parfreq(all(parsub[par[u]]));
            parfreq[hsh[sub[u]]]--;
            if (parfreq[hsh[sub[u]]] == 0)
                parfreq.erase(hsh[sub[u]]);
            vpi parv(all(parfreq));
            calc(parv);
            freq[hsh[parv]]++;
            // freq[]
        }
        vpi freqv(all(freq));
        if (sz(freq) >= 3)
        {
            return;
        }
        // cout << u << ":\n";
        // for(auto [key, val] : freqv){
        //     cout << key << "," << val << "\n";
        // }
        calc(freqv);
        if (good[hsh[freqv]])
        {
            ans = u;
            // cout << u << " can be a root\n";
        }
        parsub[u] = freqv;
        for (int v : adj[u])
        {
            reroot(v, reroot);
        }
    };
    // cout << "reroot:\n";
    reroot(0, reroot);
    cout << (ans + 1) << "\n";

    return 0;
}
