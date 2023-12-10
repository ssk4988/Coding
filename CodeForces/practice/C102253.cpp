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
ll tri(ll v){
    return v * (v-1) / 2;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    // cin.exceptions(cin.failbit);
    int cn = 0;
    int n;
    while(cin >> n)
    {
        vi c(n);
        vvi cs(n);
        rep(i, 0, n)
        {
            cin >> c[i];
            c[i]--;
            cs[c[i]].pb(i);
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
        vi par(n);
        vl subsz(n, 1);
        vi tin(n), tout(n), depth(n);
        int Time = 0;
        vl prerem(n);
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
                subsz[cur] += subsz[nex];
                prerem[cur] += tri(subsz[nex]);
            }
            tout[cur] = Time++;
        };
        dfs(0, 0, 0, dfs);
        vvi tbl = treeJump(par);
        vvi vchild(n);
        vi vpar(n, -1);
        ll ans = n * tri(n);
        rep(color, 0, n)
        {
            if(sz(cs[color]) == 0){
                ans -= tri(n);
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
            auto calc = [&](int cur, auto &&calc) -> ll {
                ll unexplored = subsz[cur]; // how much of subtree can we give to parent
                if(c[cur] == color) ans -= prerem[cur]; // first assume each real subtree contributes
                for (int i : vchild[cur]){
                    int under = jmp(tbl, i, depth[i] - depth[cur] - 1);
                    ll vs = calc(i, calc);
                    if(c[cur] == color){
                        ans += tri(subsz[under]); // recalc this subtrees contribution
                        ans -= tri((subsz[under] - subsz[i]) + vs);
                    }
                    else{
                        unexplored -= subsz[i];
                        unexplored += vs;
                    }
                }
                if(c[cur] != color){
                    return unexplored;
                }
                return 0;
            };
            ll top = n - subsz[cs[color][0]] + calc(cs[color][0], calc);
            ans -= tri(top);
            for (int j : cs[color])
            {
                vchild[j].clear();
                vpar[j] = -1;
            }
            // cout << "processed color " << color << " " << ans << endl;
        }
        cout << "Case #" << (cn + 1) << ": " << ans << endl;
        cn++;
    }

    return 0;
}
