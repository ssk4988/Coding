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

vector<vi> treeJump(vi &P)
{
    int on = 1, d = 1;
    while (on < sz(P))
        on *= 2, d++;
    vector<vi> jmp(d, P);
    rep(i, 1, d) rep(j, 0, sz(P))
        jmp[i][j] = jmp[i - 1][jmp[i - 1][j]];
    return jmp;
}

int jmp(vector<vi> &tbl, int nod, int steps)
{
    rep(i, 0, sz(tbl)) if (steps & (1 << i)) nod = tbl[i][nod];
    return nod;
}

int lca(vector<vi> &tbl, vi &depth, int a, int b)
{
    if (depth[a] < depth[b])
        swap(a, b);
    a = jmp(tbl, a, depth[a] - depth[b]);
    if (a == b)
        return a;
    for (int i = sz(tbl); i--;)
    {
        int c = tbl[i][a], d = tbl[i][b];
        if (c != d)
            a = c, b = d;
    }
    return tbl[0][a];
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n;cin >> n;
    vvi adj(n + n - 1);
    vi c(n + n - 1, -1);
    vvi cs(n + n - 1);
    rep(i, 0, n - 1)
    {
        int a, b, v;
        cin >> a >> b >> v;
        a--, b--, v--;
        c[n + i] = v;
        cs[v].pb(n + i);
        adj[a].pb(n + i);
        adj[n + i].pb(a);
        adj[b].pb(n + i);
        adj[n + i].pb(b);
    }
    int no = n;
    n += n - 1;
    vi par(n);
    vl subsz(n);
    vl subpairs(n);
    vi tin(n), tout(n), depth(n);
    int Time = 0;
    auto dfs = [&](int cur, int p, int d, auto &&dfs) -> void
    {
        par[cur] = p;
        tin[cur] = Time++;
        depth[cur] = d;
        for (int nex : adj[cur])
        {
            if (nex == p)
                continue;
            dfs(nex, cur, d + 1, dfs);
            subpairs[cur] += subsz[nex] * subsz[cur];
            subsz[cur] += subsz[nex];
        }
        subsz[cur] += cur < no;
        tout[cur] = Time++;
    };
    dfs(0, 0, 0, dfs);
    vvi tbl = treeJump(par);
    vvi vchild(n);
    vi vpar(n, -1);
    ll ans = 0;
    rep(i, 0, n) cout << i << " " << subsz[i] << " " << subpairs[i] << nL;
    rep(color, 0, n)
    {
        if(sz(cs[color]) == 0){
            continue;
        }
        sort(all(cs[color]), [&](int a, int b) -> bool
                { return tin[a] < tin[b]; });
        unordered_set<int> v1(all(cs[color]));
        rep(j, 0, sz(cs[color]) - 1)
        {
            int l = lca(tbl, depth, cs[color][j], cs[color][j + 1]);
            v1.insert(l);
        }
        cs[color] = vi(all(v1));
        sort(all(cs[color]), [&](int a, int b) -> bool
                { return tin[a] < tin[b]; });
        vi st;
        for (int j : cs[color])
        {
            while (sz(st) && lca(tbl, depth, st.back(), j) != st.back())
            {
                st.pop_back();
            }
            if (sz(st))
            {
                vchild[st.back()].pb(j);
                vpar[j] = st.back();
            }
            st.pb(j);
        }
        auto calc = [&](int cur, ll p, auto &&calc) -> ll {
            ll unexplored = subsz[cur]; // how much of subtree can we give to parent
            if(c[cur] == color) ans += subpairs[cur]; // first assume each real subtree contributes
            ll stillactive = subsz[cur] - (cur < no);
            // PARENT NOT INCLUDED YET
            for (int i : vchild[cur]){
                int under = jmp(tbl, i, depth[i] - depth[cur] - 1);
                ll parentcont = c[cur] == color ? subsz[under] - subsz[i] : p + subsz[cur] - subsz[under];
                ll vs = calc(i, parentcont, calc);
                if(c[cur] == color){
                    stillactive -= subsz[under];
                    ans -= subsz[under] * stillactive; // remove all pairs using this subtree
                    ans += vs * stillactive;
                    stillactive += vs;
                }
                else{
                    unexplored -= subsz[i];
                    unexplored += vs;
                }
            }
            if(c[cur] != color){
                return unexplored;
            }
            cout << cur << " " << stillactive << " " << p << " " << ans << nL;
            ans += p * stillactive;
            return 0;
        };
        ll top = calc(cs[color][0], no - subsz[cs[color][0]], calc);
        for (int j : cs[color])
        {
            vchild[j].clear();
            vpar[j] = -1;
        }
        cout << "processed color " << color << " " << ans << endl;
    }
    cout << ans << endl;
    

    return 0;
}
