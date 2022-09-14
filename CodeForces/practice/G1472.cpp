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

const int max_n = 200005;
const int inf = 100000000;

int dp[max_n][2];
int d[max_n];
vi adj[max_n];
bool v[max_n];

int dfs(int node, bool b)
{
    if (dp[node][b] != -1)
        return dp[node][b];
    int best = d[node];
    for (int n2 : adj[node])
    {
        if (d[n2] <= d[node])
        {
            if (b)
                best = min(best, dfs(n2, 0));
        }
        else
        {
            best = min(best, dfs(n2, b));
        }
    }
    return dp[node][b] = best;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc;
    cin >> nc;
    rep(cn, 0, nc)
    {
        int n, m;
        cin >> n >> m;
        memset(dp, -1, sizeof dp);
        memset(d, -1, sizeof d);
        memset(v, false, sizeof v);
        rep(i, 0, n)
        {
            adj[i] = {};
        }

        rep(i, 0, m)
        {
            int a, b;
            cin >> a >> b;
            a--;
            b--;
            adj[a].pb(b);
        }
        d[0] = 0;
        deque<int> q;
        q.pb(0);
        while (!q.empty())
        {
            int node = q.front();
            q.pop_front();
            if (v[node])
                continue;
            v[node] = true;
            for (int n2 : adj[node])
            {
                if (!v[n2])
                {
                    q.pb(n2);
                    d[n2] = min(d[n2] == -1 ? inf : d[n2], d[node] + 1);
                }
            }
        }
        int ans[n];
        memset(ans, -1, sizeof ans);
        rep(i, 0, n)
        {
            rep(j, 0, 2)
            {
                ans[i] = min(ans[i] == -1 ? inf : ans[i], dfs(i, j));
            }
            cout << ans[i] << " ";
        }
        cout << nL;
    }

    return 0;
}