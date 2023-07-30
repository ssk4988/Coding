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
vi bridges;
int Time;
template <class F>
int dfs(int at, int par, F &f)
{
    int me = num[at] = ++Time, e, y, top = me;
    int numchild = 0;
    bool isart = false;
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
                numchild++;
                int si = sz(st);
                int up = dfs(y, e, f);
                top = min(top, up);
                if (up >= me){
                    isart = true;
                }
                if (up == me)
                {
                    st.push_back(e);
                    st.resize(si);
                }
                else if (up < me)
                    st.push_back(e);
                else
                {
                    /* e is a bridge */
                    bridges.pb(e);
                }
            }
        }
    if(isart && (at != 0 || numchild > 1)) f(at);
    return top;
}

template <class F>
void bicomps(F f)
{
    num.assign(sz(ed), 0);
    rep(i, 0, sz(ed)) if (!num[i]) dfs(i, -1, f);
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m;
    cin >> n >> m;
    vector<vpi> g(n);
    vpi edges(m);
    rep(i, 0, m)
    {
        int a, b;
        cin >> a >> b;
        edges[i] = {a, b};
        a--, b--;
        g[a].pb({b, i});
        g[b].pb({a, i});
    }
    ed = g;
    vi artpoints(n);
    int numpts = 0;
    bicomps([&](int stuff)->void{
        artpoints[stuff] = true;
        numpts++;
    });
    cout << numpts << nL;
    rep(i, 0, n){
        if(artpoints[i]) cout << (i + 1) << " ";
    }
    cout << nL;
    return 0;
}