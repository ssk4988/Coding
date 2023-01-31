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
        // cout << "reached start" << nL;
        rep(i, 0, ptr)
        {
            int x = q[i];
            for (auto e : graph[x])
            {
                if (par[e.first] == -1 && e.second < graph1[x][e.first])
                {
                    par[e.first] = x;
                    q[ptr++] = e.first;
                    if (e.first == sink)
                        goto out;
                }
            }
            // cout << i << " " << ptr << nL;
        }
        // cout << "reached end" << nL;
        rep(i, 0, rs.size()){
            reverse(all(rs[i]));
        }
        return rs;
    out:
        // cout << "add route" << nL;
        rs.pb({});
        for (int y = sink; y != source; y = par[y]){
            graph[par[y]][y]++;
            graph[y][par[y]]--;
            // if(graph[par[y]][y] == graph1[par[y]][y]){
            //     graph[par[y]].erase(y);
            // }
            // if(graph[y][par[y]] == graph1[y][par[y]]){
            //     graph[y].erase(par[y]);
            // }
            rs.back().pb(y);
        }
        rs.back().pb(source);
    }
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m;
    cin >> n >> m;
    vector<unordered_map<int, int>> graph(n), graph1(n);
    rep(i, 0, m)
    {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        graph1[a][b] = graph[a][b] = 1;

        // if(graph[b].find(a) != graph[b].end()){
        //     cout << "contains reverse edge" << nL;
        // }
    }
    int mf = edmondsKarp(graph, 0, n - 1);
    cout << mf << nL;
    rep(i, 0, n){
        for(auto &p : graph1[i]){
            graph[i][p.f];
        }
    }
    vvi rs = routes(graph, graph1, 0, n - 1);
    // cout << "routes found: " << rs.size() << nL;
    rep(i, 0, rs.size()){
        cout << rs[i].size() << nL;
        rep(j, 0, rs[i].size()){
            cout << (rs[i][j] + 1);
            if(j + 1 < rs[i].size()){
                graph1[rs[i][j]][rs[i][j+1]]--;
                if(graph1[rs[i][j]][rs[i][j+1]]<0){
                    cout << "illegal edge to use" << nL;
                }
                cout << " ";
            }
        }
        cout << nL;
    }

    return 0;
}
