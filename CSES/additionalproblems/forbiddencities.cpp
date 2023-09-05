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

int n, m, q;
vi belong;
vi num, st;
vector<vector<pi>> ed;
int Time;
int ncomps = 0;
template <class F>
int dfs(int at, int par, F &f)
{
    int me = num[at] = ++Time, e, y, top = me;
    for (auto pa : ed[at])
        if (pa.second != par)
        {
            tie(y, e) = pa;
            if (num[y])
            {
                top = min(top, num[y]);
                if (num[y] < me)
                    st.push_back(e);
            }
            else
            {
                int si = sz(st);
                int up = dfs(y, e, f);
                top = min(top, up);
                if (up >= me)
                {
                    // cout << at << " to " << y << nL;
                    st.push_back(e);
                    f(vi(st.begin() + si, st.end()));
                    st.resize(si);
                }
                else if (up < me)
                    st.push_back(e);
                else
                { /* e is a bridge */
                }
            }
        }
    return top;
}

template <class F>
void bicomps(F f)
{
    num.assign(sz(ed), 0);
    rep(i, 0, sz(ed)) if (!num[i]) dfs(i, -1, f);
}
void assign(vi e)
{
    for (int i : e)
    {
        belong[i] = ncomps;
        // cout << i << " " << ncomps << nL;
    }
    ncomps++;
}
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
    cin >> n >> m >> q;
    belong.resize(m);
    // vector<vpi> adj(n);
    ed.resize(n);
    rep(i, 0, m)
    {
        int a, b;
        cin >> a >> b;
        a--, b--;
        ed[a].pb({b, i});
        ed[b].pb({a, i});
        // cout << "connect " << a << " to " << b << nL;
    }
    bicomps(assign);
    unordered_map<int, int> rl;
    vi isart(n);
    // cout << ncomps << nL;
    // rep(i, 0, m) cout << belong[i] << nL;
    rep(i, 0, n)
    {
        unordered_set<int> bccs;
        for (auto [b, id] : ed[i])
        {
            bccs.insert(belong[id]);
        }
        if (sz(bccs) > 1)
        {
            rl[i] = ncomps++;
            isart[i] = true;
        }
        else
            rl[i] = *bccs.begin();
        // cout << i << " is now " << rl[i] << nL;
    }
    vvi adj(ncomps);
    rep(i, 0, n)
    {
        if (!isart[i])
            continue;
        unordered_set<int> bccs;
        for (auto [b, id] : ed[i])
        {
            bccs.insert(belong[id]);
        }
        for (int id : bccs)
        {
            adj[id].pb(rl[i]);
            adj[rl[i]].pb(id);
        }
    }
    LCA lc(adj);
    rep(i, 0, q)
    {
        int a, b, c;
        cin >> a >> b >> c;
        a--, b--, c--;
        if(a == c || b == c){
            cout << "NO\n";
            continue;
        }
        a = rl[a], b = rl[b];
        
        if (a == b || !isart[c])
        {
            cout << "YES\n";
            continue;
        }
        
        c = rl[c];
        int l = lc.lca(a, b);
        if (lc.lca(l, c) == l && (lc.lca(a, c) == c || lc.lca(b, c) == c))
        {
            cout << "NO\n";
        }
        else
            cout << "YES\n";
    }

    return 0;
}
