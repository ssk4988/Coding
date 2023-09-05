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
    // int nc; cin >> nc;
    // rep(cn, 0, nc){
    string str;
    cin >> str;
    int n = sz(str) - 1;
    int cnt = n;
    map<string, int> rl;
    rep(i, 0, n)
    {
        if (rl.count(str.substr(i, 2)) == 0)
        {
            rl[str.substr(i, 2)] = cnt++;
        }
    }
    vector<vpi> adj(cnt), radj(cnt);
    rep(i, 0, n)
    {
        adj[i].pb({rl[str.substr(i, 2)], 1});
        adj[rl[str.substr(i, 2)]].pb({i, 0});
        radj[rl[str.substr(i, 2)]].pb({i, 1});
        radj[i].pb({rl[str.substr(i, 2)], 0});
    }
    rep(i, 0, n)
    {
        adj[i].pb({i + 1, 1});
        adj[i + 1].pb({i, 1});
        radj[i].pb({i + 1, 1});
        radj[i + 1].pb({i, 1});
    }
    int q;
    cin >> q;
    vi ans(q, 3 * (n + 5));
    vpi qs(q);
    rep(i, 0, q)
    {
        cin >> qs[i].f >> qs[i].s;
        qs[i].f--, qs[i].s--;
        ans[i] = abs(qs[i].f - qs[i].s);
    }
    rep(i, n, cnt)
    {
        vi c(cnt, INT_MAX);
        c[i] = 0;
        // inq[i] = true;
        deque<int> dq;
        dq.push_back(i);
        while (dq.size())
        {
            int k = dq.front();
            dq.pop_front();
            for (auto [nex, w] : adj[k])
            {
                if(c[nex] <= c[k] + w) continue;
                c[nex] = min(c[nex], c[k] + w);
                if (w == 0)
                    dq.push_front(nex);
                else
                    dq.pb(nex);
            }
        }
        // v = vi(cnt);
        vi c1 = vi(cnt, INT_MAX);
        c1[i] = 0;
        dq.pb(i);
        while (dq.size())
        {
            int k = dq.front();
            dq.pop_front();
            for (auto [nex, w] : radj[k])
            {
                if(c1[nex] <= c1[k] + w) continue;
                c1[nex] = min(c1[nex], c1[k] + w);
                if (w == 0)
                    dq.push_front(nex);
                else
                    dq.pb(nex);
            }
        }
        rep(j, 0, cnt){
            cout << c[j] << " ";
        }
        cout << nL;
        rep(j, 0, q)
        {
            ans[j] = min(ans[j], -1 + c1[qs[j].f] + c1[qs[j].s]);
        }
    }
    rep(j, 0, q)
    {
        cout << ans[j] << nL;
    }
    // }

    return 0;
}
