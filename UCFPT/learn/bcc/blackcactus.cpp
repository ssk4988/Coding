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

vi num, st;
vector<vector<pi>> ed;
vi depth;
ll ans = 1;

void mult(ll multiplier)
{
    ans = (ans * multiplier) % 1007;
}

int Time;
int dfs(int at, int par, int d)
{
    int me = num[at] = ++Time, e, y, top = me;
    depth[at] = d;
    for (auto pa : ed[at])
        if (pa.second != par)
        {
            tie(y, e) = pa;
            if (num[y])
            {
                top = min(top, num[y]);
                if (num[y] < me)
                {
                    st.push_back(e);
                    mult(abs(depth[at] - depth[y]) + 1);
                }
            }
            else
            {
                int si = sz(st);
                int up = dfs(y, e, d + 1);
                top = min(top, up);
                if (up == me)
                {
                    st.push_back(e);
                    // f(vi(st.begin() + si, st.end()));
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

int v, e, nc;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cin >> nc;
    rep(cn, 0, nc)
    {
        cin >> v >> e;
        ed = vector<vpi>(v);
        num = vi(v), st = vi(v), depth = vi(v);
        Time = 0;
        ans = 1;
        num.assign(sz(ed), 0);
        rep(i, 0, e)
        {
            int a, b;
            cin >> a >> b;
            a--,b--;
            ed[a].pb({b, i});
            ed[b].pb({a, i});
        }
        rep(i, 0, sz(ed)) if (!num[i]) dfs(i, -1, 0);
        cout << "Case #" << (cn + 1) << ": " << ans << nL << nL;
    }

    return 0;
}
