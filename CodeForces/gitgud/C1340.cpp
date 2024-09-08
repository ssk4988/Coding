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

// dp[i][v] = t
// safety index i, time v mod g, min time to reach it
// dp[i][v] -> dp[i-1][v + trav] + trav

// impossible if max difference in d is > g

const int D = 1e7+1000;
vi pq[D];
const int G = 1001;
const int M = 10000;
int dp[M][G];

int n, m;

// inline int getidx(int )

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cin >> n >> m;
    vi x(m);
    rep(i, 0, m) cin >> x[i];
    sort(all(x));
    int mxd = 0;
    rep(i, 1, m) mxd = max(mxd, x[i] - x[i - 1]);
    int g, r;
    cin >> g >> r;
    if (mxd > g)
    {
        cout << -1 << "\n";
        return 0;
    }
    const int oo = 1e9;
    rep(i, 0, m){
        rep(j, 0, g+1) dp[i][j] = oo;
    }
    // vector dp(m, vl(g + 1, oo));
    // vector<vpi> pq(1);
    pq[0].pb(0);
    // priority_queue<pair<ll, pi>, vector<pair<ll, pi>>, greater<>> pq;
    // rep(t, 0, 1)
    // pq.push({t, {0, t}});
    rep(d, 0, D)
    {
        rep(v, 0, sz(pq[d]))
        {
            auto ac = pq[d][v];
            int i = ac / G, t = ac % G;
            // auto [i, t] = pq[d][v];
            if (dp[i][t] != oo)
                continue;
            // cout << i << " " << t << " " << d << endl;
            dp[i][t] = d;
            if (t == g)
            {
                // while(sz(pq) <= d + r) pq.pb({});
                pq[d+r].pb(i * G);
                // pq[d + r].pb(pi{i, 0});
                continue;
            }
            if (i > 0 && t + x[i] - x[i - 1] <= g)
            {
                int t2 = t + x[i] - x[i - 1];
                int w = x[i] - x[i - 1];
                // while(sz(pq) <= d + w) pq.pb({});
                pq[d + w].pb((i - 1) * G + t2);
                // pq[d + w].pb(pi{i - 1, t2});
            }
            if (i + 1 < m && t + x[i + 1] - x[i] <= g)
            {
                int t2 = t + x[i + 1] - x[i];
                int w = x[i + 1] - x[i];
                // while(sz(pq) <= d + w) pq.pb({});
                pq[d + w].pb((i + 1) * G + t2);
                // pq[d + w].pb(pi{i + 1, t2});
            }
        }
    }
    
    int dist = dp[m-1][0];
    rep(i, 0, g+1) dist = min(dist, dp[m-1][i]);
    if (dist == oo)
        dist = -1;
    cout << dist << "\n";

    return 0;
}
