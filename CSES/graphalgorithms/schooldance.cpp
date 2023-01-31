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

template <class T>
T edmondsKarp(vector<unordered_map<int, T>> &graph, int source, int sink)
{
    assert(source != sink);
    T flow = 0;
    vi par(sz(graph)), q = par;

    for (;;)
    {
        fill(all(par), -1);
        par[source] = 0;
        int ptr = 1;
        q[0] = source;

        rep(i, 0, ptr)
        {
            int x = q[i];
            for (auto e : graph[x])
            {
                if (par[e.first] == -1 && e.second > 0)
                {
                    par[e.first] = x;
                    q[ptr++] = e.first;
                    if (e.first == sink)
                        goto out;
                }
            }
        }
        return flow;
    out:
        T inc = numeric_limits<T>::max();
        for (int y = sink; y != source; y = par[y])
            inc = min(inc, graph[par[y]][y]);

        flow += inc;
        for (int y = sink; y != source; y = par[y])
        {
            int p = par[y];
            if ((graph[p][y] -= inc) <= 0)
                graph[p].erase(y);
            graph[y][p] += inc;
        }
    }
}

vvi routes(vector<unordered_map<int, int>> &graph, vector<unordered_map<int, int>> &graph1, int source, int sink)
{
    vi par(sz(graph)), q = par;
    vvi rs;
    for (;;)
    {
        fill(all(par), -1);
        par[source] = source;
        int ptr = 1;
        q[0] = source;
        rep(i, 0, ptr)
        {
            int x = q[i];
            for (auto &e : graph[x])
            {
                if (par[e.f] == -1 && e.second < graph1[x][e.f])
                {
                    par[e.f] = x;
                    q[ptr++] = e.f;
                    if (e.f == sink)
                        goto out;
                }
            }
        }
        return rs;
    out:
        rs.pb({sink});
        for (int y = sink; y != source; y = par[y])
        {
            graph[par[y]][y]++;
            graph[y][par[y]]--;
            rs.back().pb(par[y]);
        }
        reverse(all(rs.back()));
    }
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m, k;
    cin >> n >> m >> k;
    vector<unordered_map<int, int>> graph(n + m + 2), graph1(n + m + 2);
    rep(i, 0, k)
    {
        int a, b;
        cin >> a >> b;
        graph[a][b + n] = 1;
    }
    rep(i, 1, n + 1)
    {
        graph[0][i] = 1;
    }
    rep(i, 1, m + 1)
    {
        graph[i + n][n + m + 1] = 1;
    }
    rep(i, 0, graph.size())
    {
        graph1[i] = graph[i];
    }
    int mf = edmondsKarp(graph, 0, n + m + 1);
    cout << mf << nL;
    rep(i, 0, graph.size())
    {
        for (auto &e : graph1[i])
        {
            graph[i][e.f];
        }
    }
    vvi rs = routes(graph, graph1, 0, n + m + 1);
    rep(i, 0, rs.size())
    {
        cout << rs[i][1] << " " << (rs[i][2] - n) << nL;
    }

    return 0;
}
