#include <bits/stdc++.h>
using namespace std;

using ll = long long;
// using double = long double;
using pi = pair<int, int>;
using pl = pair<ll, ll>;
using pd = pair<double, double>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<double>;
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
const double inf = 1e15;
pair<double, vi> hungarian(const vector<vd> &a)
{
    if (a.empty())
        return {0, {}};
    int n = sz(a) + 1, m = sz(a[0]) + 1;
    vd u(n), v(m);
    vi p(m), ans(n - 1);
    rep(i, 1, n)
    {
        p[0] = i;
        int j0 = 0; // add "dummy" worker 0
        vd dist(m, inf);
        vi pre(m, -1);
        vector<bool> done(m + 1);
        do
        { // dijkstra
            done[j0] = true;
            int i0 = p[j0], j1;
            double delta = inf;
            rep(j, 1, m) if (!done[j])
            {
                auto cur = a[i0 - 1][j - 1] - u[i0] - v[j];
                if (cur < dist[j])
                    dist[j] = cur, pre[j] = j0;
                if (dist[j] < delta)
                    delta = dist[j], j1 = j;
            }
            rep(j, 0, m)
            {
                if (done[j])
                    u[p[j]] += delta, v[j] -= delta;
                else
                    dist[j] -= delta;
            }
            j0 = j1;
        } while (p[j0]);
        while (j0)
        { // update alternating path
            int j1 = pre[j0];
            p[j0] = p[j1], j0 = j1;
        }
    }
    rep(j, 1, m) if (p[j]) ans[p[j] - 1] = j - 1;
    return {-v[0], ans}; // min cost
}
const int MAX_D = 16;
double dist[MAX_D][MAX_D];
double dp[1 << MAX_D][MAX_D];
int cur_d;

double tsp(vpi &v)
{
    int d = sz(v);
    rep(k, 0, d)
    {
        rep(l, 0, d)
        {
            dist[k][l] = sqrtl((v[k].f - v[l].f) * (v[k].f - v[l].f) + (v[k].s - v[l].s) * (v[k].s - v[l].s));
        }
    }
    cur_d = d;
    rep(i, 0, 1 << d)
    {
        rep(j, 0, d)
        {
            dp[i][j] = inf;
        }
    }
    dp[1 << 0][0] = 0;
    rep(mask, 0, 1 << d)
    {
        rep(pre, 0, d)
        {
            rep(k, 0, cur_d)
            {
                if ((mask >> k) & 1)
                    dp[mask][pre] = min(dp[mask][pre], dp[mask ^ (1 << pre)][k] + dist[pre][k]);
            }
        }
    }

    double ans = inf;
    rep(k, 0, d)
    {
        ans = min(ans, dist[0][k] + dp[(1 << d) - 1][k]);
    }
    return ans;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n;
    cin >> n;
    vector<vpi> a(n / 2), b(n / 2);
    rep(i, 0, n / 2)
    {
        int d;
        cin >> d;
        a[i].resize(d);
        rep(j, 0, d) cin >> a[i][j].f >> a[i][j].s;
    }
    rep(i, 0, n / 2)
    {
        int d;
        cin >> d;
        b[i].resize(d);
        rep(j, 0, d) cin >> b[i][j].f >> b[i][j].s;
    }

    vector<vd> cost(n / 2, vd(n / 2));
    rep(i, 0, n / 2)
    {
        rep(j, 0, n / 2)
        {
            vpi v(a[i]);
            rep(k, 0, sz(b[j])) v.pb(b[j][k]);
            cost[i][j] = tsp(v);
            // cout << i << " " << j << " " << cost[i][j] << "\n";
        }
    }
    double orig = 0;
    rep(i, 0, n / 2) orig += tsp(a[i]) + tsp(b[i]);

    auto [d, mt] = hungarian(cost);
    cout << fixed << setprecision(8) << orig << " " << d << "\n";

    return 0;
}
