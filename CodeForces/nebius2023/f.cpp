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

vpi edges, qs;
vi ans;
vvi adj;
void calc(int qidx)
{
    if (ans[qidx] != -1)
        return;
    vi dist(n, INT_MAX);
    vvi adj1(n);
    rep(i, 0, qidx)
    {
        auto [u, v] = qs[i];
        adj1[u].pb(v);
        adj1[v].pb(u);
    }
    dist[0] = 0;
    queue<int> pq;
    pq.push(0);
    while (pq.size())
    {
        int x = pq.front();
        pq.pop();
        for (int i : adj[x])
        {
            if (dist[i] == INT_MAX)
            {
                dist[i] = 1 + dist[x];
                pq.push(i);
            }
        }
        for (int i : adj1[x])
        {
            if (dist[i] == INT_MAX)
            {
                dist[i] = 1 + dist[x];
                pq.push(i);
            }
        }
    }
    int farthest = 0;
    rep(i, 0, n) farthest = max(farthest, dist[i]);
    ans[qidx] = farthest;
}
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cin >> n >> m >> q;
    edges.resize(m), qs.resize(q);
    adj.resize(n);
    rep(i, 0, m)
    {
        cin >> edges[i].f >> edges[i].s;
        edges[i].f--, edges[i].s--;
        auto [u, v] = edges[i];
        adj[u].pb(v);
        adj[v].pb(u);
    }
    rep(i, 0, q)
    {
        cin >> qs[i].f >> qs[i].s;
        qs[i].f--, qs[i].s--;
    }
    ans = vi(q + 1, -1);
    vi res(q + 1);
    auto solve = [&](int l, int r, auto &&solve)->void{
        // if(l == r){
        //     calc(l);
        //     res[l] = ans[l];
        //     return;
        // }
        calc(l);
        calc(r);
        if(ans[r] * 2 >= ans[l]){
            res[l] = ans[l];
            rep(i, l + 1, r) res[i] = 2 * ans[r];
            res[r] = ans[r];
            return;
        }
        int mid = (l + r) / 2;
        solve(l, mid, solve);
        solve(mid + 1, r, solve);
    };
    solve(0, q, solve);
    rep(i, 0, q + 1) cout << res[i] << " ";
    cout << nL;
    // int pre = 0;
    // calc(0);
    // cout << ans[0] << " ";
    // while (pre < q)
    // {
    //     int lo = 1, hi = q - pre;
    //     while (lo < hi)
    //     {
    //         int mid = lo + (hi - lo + 1) / 2;
    //         calc(mid + pre);
    //         if (ans[mid + pre] * 2 >= ans[pre])
    //         {
    //             lo = mid;
    //         }
    //         else
    //             hi = mid - 1;
    //     }
    //     calc(pre + lo);
    //     rep(i, 1, lo) cout << 2 * ans[pre + lo] << " ";
    //     cout << ans[pre + lo] << " ";
    //     pre = pre + lo;
    // }
    // cout << nL;

    return 0;
}
