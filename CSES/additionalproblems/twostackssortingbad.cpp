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

struct UF
{
    vi e;
    UF(int n) : e(n, -1) {}
    bool sameSet(int a, int b) { return find(a) == find(b); }
    int size(int x) { return -e[find(x)]; }
    int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
    bool join(int a, int b)
    {
        a = find(a), b = find(b);
        if (a == b)
            return false;
        if (e[a] > e[b])
            swap(a, b);
        e[a] += e[b];
        e[b] = a;
        return true;
    }
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n;
    cin >> n;
    vi p(n), inv(n);
    rep(i, 0, n)
    {
        cin >> p[i];
        p[i]--;
        inv[p[i]] = i;
    }
    vi nxt(n, n);
    vi st;
    for (int i = n - 1; i >= 0; i--)
    {
        while (sz(st) && p[st.back()] < p[i])
            st.pop_back();
        if (sz(st))
            nxt[i] = st.back();
        st.push_back(i);
    }
    // rep(i, 0, n) cout << nxt[i] << " ";
    // cout << "\n";
    vvi adj(n);
    UF uf(n);
    auto eq = [&](int a, int b) -> void {
        uf.join(a, b);
        cout << "eq " << a << " " << b << "\n";
    };
    auto neq = [&](int a, int b) -> void {
        adj[a].pb(b);
        adj[b].pb(a);
        cout << "neq " << a << " " << b << "\n";
    };
    vvi starts(n), ends(n+1);
    vi start(n), end(n);
    for (int cur = 0; cur < n; cur++)
    {
        int last = cur;
        while (last + 1 < n && inv[last + 1] < inv[last])
        {
            eq(inv[last], inv[last + 1]);
            last++;
        }
        starts[inv[last]].pb(uf.find(inv[cur]));
        ends[inv[cur]+1].pb(uf.find(inv[cur]));
        start[uf.find(inv[cur])] = inv[last];
        end[uf.find(inv[cur])] = inv[cur]+1;
        cur = last;
    }
    bool imp = false;
    set<int> cur;
    rep(i, 0, n){
        for(int j : ends[i]) cur.erase(j);
        for(int j : starts[i]) cur.insert(j);
        if(sz(cur) > 2) {
            imp = true;
            break;
        }
        for(int j1 : cur){
            cout << "at " << i << " has " << j1 << "\n";
            for(int j2 : cur){
                if(j1 != j2) neq(j1, j2);
            }
        }
    }
    if(imp){
        cout << "IMPOSSIBLE\n";
        return 0;
    }
    vvi comps(n);
    rep(i, 0, n) comps[uf.find(i)].pb(i);
    vi state(n);
    vi val(n);
    auto dfs = [&](int c, int t, auto &&dfs) -> bool
    {
        if (state[c])
            return val[c] != t;
        state[c] = 1;
        val[c] = t;
        for (int u : comps[c])
        {
            for (int v : adj[u])
            {
                if (uf.find(v) == c)
                    continue;
                if (dfs(uf.find(v), !t, dfs))
                    return true;
            }
        }
        return false;
    };
    rep(i, 0, n)
    {
        if (sz(comps[i]) && state[i] == 0 && dfs(i, 0, dfs))
            imp = true;
    }
    if (imp)
    {
        cout << "IMPOSSIBLE\n";
    }
    else
    {
        rep(i, 0, n)
        {
            cout << val[uf.find(i)] + 1 << " ";
        }
        cout << "\n";
    }

    return 0;
}
