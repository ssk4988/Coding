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

template <class T>
struct RMQ
{
    vector<vector<T>> jmp;
    RMQ(const vector<T> &V) : jmp(1, V)
    {
        for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k)
        {
            jmp.emplace_back(sz(V) - pw * 2 + 1);
            rep(j, 0, sz(jmp[k]))
                jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
        }
    }
    T query(int a, int b)
    {
        assert(a < b); // or return inf if a == b
        int dep = 31 - __builtin_clz(b - a);
        return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
    }
};

struct LCA
{
    int T = 0;
    vi time, path, ret;
    RMQ<int> rmq;

    LCA(vector<vi> &C) : time(sz(C)), rmq((dfs(C, 0, -1), ret)) {}
    void dfs(vector<vi> &C, int v, int par)
    {
        time[v] = T++;
        for (int y : C[v])
            if (y != par)
            {
                path.push_back(v), ret.push_back(time[v]);
                dfs(C, y, v);
            }
    }

    int lca(int a, int b)
    {
        if (a == b)
            return a;
        tie(a, b) = minmax(time[a], time[b]);
        return path[rmq.query(a, b)];
    }
    // dist(a,b){return depth[a] + depth[b] - 2*depth[lca(a,b)];}
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vvi adj(n);
    rep(i, 0, n - 1)
    {
        int a, b;
        cin >> a >> b;
        a--, b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    LCA lca(adj);
    int q;
    cin >> q;
    vvi vadj(n);
    rep(_, 0, q)
    {
        int c;
        cin >> c;
        vi v(c);
        rep(j, 0, c) {cin >> v[j]; v[j]--;}
        sort(all(v), [&](int a, int b) -> bool
             { return lca.time[a] < lca.time[b]; });
        unordered_set<int> v1(all(v)); 
        rep(j, 0, c - 1)
        {
            int l = lca.lca(v[j], v[j + 1]);
            v1.insert(l);
        }
        v = vi(all(v1));
        sort(all(v), [&](int a, int b) -> bool
             { return lca.time[a] < lca.time[b]; });
        vi st;
        for(int j : v){
            while(sz(st) && lca.lca(st.back(), j) != st.back()) st.pop_back();
            if(sz(st)){
                vadj[st.back()].pb(j);
                vadj[j].pb(st.back());
            }
            st.pb(j);
        }
        unordered_map<int, int> freq;
        for(int j : v) freq[sz(vadj[j])]++;
        int expt1 = min(2, sz(v)), expt2 = sz(v) - expt1;
        if((c == 1) || (freq[1] == expt1 && freq[2] == expt2)) cout << "YES\n";
        else cout << "NO\n";
        // for(auto [key, val] : freq) cout << key << " " << val << nL;
        // cout << sz(v) << nL;
        // for(int j : v) cout << j << " ";
        // cout << nL;
        for(int j : v) vadj[j].clear();
    }

    return 0;
}
