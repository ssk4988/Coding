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
    int nc;
    cin >> nc;
    rep(cn, 0, nc)
    {
        int n, q;
        cin >> n >> q;
        vi c(n);
        vi frq(n + 1);
        int numon = 0;
        vi cbl(n);
        rep(i, 0, n)
        {
            cin >> c[i];
        }
        vvi adj(n);
        rep(i, 0, n - 1)
        {
            int a, b;
            cin >> a >> b;
            a--, b--;
            adj[a].pb(b);
            adj[b].pb(a);
        }
        vi par(n, -1);
        auto dfs = [&](int u, int p, auto &&dfs) -> void
        {
            par[u] = p;
            for (int v : adj[u])
            {
                if (v == p)
                    continue;
                dfs(v, u, dfs);
            }
        };
        dfs(0, -1, dfs);
        LCA lc(adj);
        // rep(i, 0, n) cout << i << " "<< par[i] << "\n";
        set<int> leaves;
        auto toggle = [&](int x) -> void
        {
            if (par[x] != -1)
            {
                if (c[par[x]])
                {
                    if(cbl[par[x]] == 0) leaves.erase(par[x]);
                    frq[cbl[par[x]]]--;
                }
                cbl[par[x]] += c[x] ? -1 : 1;
                if (c[par[x]])
                {
                    frq[cbl[par[x]]]++;
                    if(cbl[par[x]] == 0) leaves.insert(par[x]);
                }
            }
            frq[cbl[x]] += c[x] ? -1 : 1;
            numon += c[x] ? -1 : 1;
            c[x] = !c[x];
            if(cbl[x] == 0){
                if(c[x])leaves.insert(x);
                else leaves.erase(x);
            } 
            // cout << "toggled " << x << "\n";
            // cout << frq[0] << " " << frq[1] << " " << frq[2] << "\n";
        };
        vi c1(c);
        c = vi(n);
        rep(i, 0, n)
        {
            if (c1[i])
            {
                toggle(i);
            }
        }
        // rep(i, 0,n) cout << cbl[i] << " ";
        // cout << "\n";
        rep(i, 0, q)
        {
            int x;
            cin >> x;
            x--;
            toggle(x);
            if (numon == 0)
            {
                cout << "NO\n";
                continue;
            }
            if (numon == 1)
            {
                cout << "YES\n";
                continue;
            }
            if ((frq[0] == 1 && frq[1] == numon - 1))
            {
                cout << "YES\n";
            }
            else
            {
                if(frq[0] == 2 && frq[2] == 1 && frq[1] == numon - 3){
                    int l1 = *leaves.begin(), l2 = *leaves.rbegin();
                    int l = lc.lca(l1, l2);
                    // cout << "lca: " << l << " " << l1 << " " << l2 << "\n";
                    if(par[l] == -1 || !c[par[l]]){
                        cout << "YES\n";
                        continue;
                    }
                }
                cout << "NO\n";
            }
        }
    }

    return 0;
}
