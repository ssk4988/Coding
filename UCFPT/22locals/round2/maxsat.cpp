#include <bits/stdc++.h>
using namespace std;
#include <bits/extc++.h>

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pl = pair<ll, ll>;
using pd = pair<ld, ld>;
using vi = vector<int>;
using vd = vector<ld>;
using vpi = vector<pii>;
using vpl = vector<pl>;
using vpd = vector<pd>;
using vvi = vector<vi>;

#define mp make_pair
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define nL "\n"

/**
 * Author: Stanford
 * Date: Unknown
 * Source: Stanford Notebook
 * Description: Min-cost max-flow. cap[i][j] != cap[j][i] is allowed; double edges are not.
 *  If costs can be negative, call setpi before maxflow, but note that negative cost cycles are not supported.
 *  To obtain the actual flow, look at positive values only.
 * Status: Tested on kattis:mincostmaxflow, stress-tested against another implementation
 * Time: Approximately O(E^2)
 */

// #include <bits/extc++.h> /// include-line, keep-include

const ll INF = numeric_limits<ll>::max() / 4;
typedef vector<ll> VL;

struct MCMF
{
    int N;
    vector<vi> ed, red;
    vector<VL> cap, flow, cost;
    vi seen;
    VL dist, pi;
    vector<pii> par;

    MCMF(int N) : N(N), ed(N), red(N), cap(N, VL(N)), flow(cap), cost(cap),
                  seen(N), dist(N), pi(N), par(N) {}

    void addEdge(int from, int to, ll cap, ll cost)
    {
        this->cap[from][to] = cap;
        this->cost[from][to] = cost;
        ed[from].push_back(to);
        red[to].push_back(from);
    }

    void path(int s)
    {
        fill(all(seen), 0);
        fill(all(dist), INF);
        dist[s] = 0;
        ll di;

        __gnu_pbds::priority_queue<pair<ll, int>> q;
        vector<decltype(q)::point_iterator> its(N);
        q.push({0, s});

        auto relax = [&](int i, ll cap, ll cost, int dir)
        {
            ll val = di - pi[i] + cost;
            if (cap && val < dist[i])
            {
                dist[i] = val;
                par[i] = {s, dir};
                if (its[i] == q.end())
                    its[i] = q.push({-dist[i], i});
                else
                    q.modify(its[i], {-dist[i], i});
            }
        };

        while (!q.empty())
        {
            s = q.top().second;
            q.pop();
            seen[s] = 1;
            di = dist[s] + pi[s];
            for (int i : ed[s])
                if (!seen[i])
                    relax(i, cap[s][i] - flow[s][i], cost[s][i], 1);
            for (int i : red[s])
                if (!seen[i])
                    relax(i, flow[i][s], -cost[i][s], 0);
        }
        rep(i, 0, N) pi[i] = min(pi[i] + dist[i], INF);
    }

    pair<ll, ll> maxflow(int s, int t)
    {
        ll totflow = 0, totcost = 0;
        while (path(s), seen[t])
        {
            ll fl = INF;
            for (int p, r, x = t; tie(p, r) = par[x], x != s; x = p)
                fl = min(fl, r ? cap[p][x] - flow[p][x] : flow[x][p]);
            totflow += fl;
            for (int p, r, x = t; tie(p, r) = par[x], x != s; x = p)
                if (r)
                    flow[p][x] += fl;
                else
                    flow[x][p] -= fl;
        }
        rep(i, 0, N) rep(j, 0, N) totcost += cost[i][j] * flow[i][j];
        return {totflow, totcost};
    }

    // If some costs can be negative, call this before maxflow:
    void setpi(int s)
    { // (otherwise, leave this out)
        fill(all(pi), INF);
        pi[s] = 0;
        int it = N, ch = 1;
        ll v;
        while (ch-- && it--)
            rep(i, 0, N) if (pi[i] != INF) for (int to : ed[i]) if (cap[i][to]) if ((v = pi[i] + cost[i][to]) < pi[to])
                pi[to] = v,
                ch = 1;
        assert(it >= 0); // negative cost cycle
    }
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, s, k;
    cin >> n >> s >> k;
    vvi adj(n, vi(s, 0));
    vpi maxsat;
    rep(i, 0, n)
    {
        int best = 0;
        rep(j, 0, s)
        {
            cin >> adj[i][j];
            best = max(best, adj[i][j]);
        }
        maxsat.pb({best, i});
    }
    sort(all(maxsat));
    reverse(all(maxsat));
    ll ans = 0;
    // rep(i, 0, n - s * k)
    // {
    //     ans += maxsat[i].first;
    // }
    MCMF flow(n + s + 4);
    // source is n + s, sink is n + s + 1
    // rep(i, n - s * k, n)
    rep(i, 0, n)
    {
        rep(j, 0, s)
        {
            flow.addEdge(maxsat[i].second, n + j, 1, -adj[maxsat[i].second][j]);
        }
        flow.addEdge(n + s, maxsat[i].second, 1, 0);
    }
    rep(j, 0, s)
    {
        flow.addEdge(n + j, n + s + 1, k, 0);
        flow.addEdge(n + j, n + s + 2, 1000, 1000);
    }
    flow.addEdge(n + s + 1, n + s + 3, 1000, 0);
    flow.addEdge(n + s + 2, n + s + 3, 1000, 0);
    flow.setpi(n + s);
    flow.maxflow(n + s, n + s + 3);
    rep(i, 0, n)
    {
        bool use = false;
        int best = -1;
        rep(j, 0, s)
        {
            best = max(best, adj[i][j]);
            if (flow.flow[i][n + j])
            {
                ans += adj[i][j];
                use = true;
                break;
            }
        }
        if(!use){
            ans += best;
            cout << "NOT USE" << nL;
        }
    }
    cout << ans << nL;

    return 0;
}
