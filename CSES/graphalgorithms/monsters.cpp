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
    int n, m;
    cin >> n >> m;
    vvi grid(n, vi(m));
    pi a;
    vvi ds = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    vvi dist(n, vi(m, INT_MAX));
    vvi visited(n, vi(m));
    priority_queue<pair<int, pi>, vector<pair<int, pi>>, greater<pair<int, pi>>> pq;
    vpi monsters;
    rep(i, 0, n)
    {
        string str;
        cin >> str;
        rep(j, 0, m)
        {
            grid[i][j] = str[j] != '#';
            if (str[j] == 'A')
                a = {i, j};
            if (str[j] == 'M')
            {
                monsters.pb({i, j});
                dist[i][j] = 0;
                pq.push({0, {i, j}});
            }
        }
    }
    string dir = "DRUL";

    while (!pq.empty())
    {
        auto p = pq.top();
        pq.pop();
        auto [i, j] = p.s;
        if (visited[i][j])
            continue;
        visited[i][j] = true;
        rep(k, 0, 4)
        {
            int i1 = i + ds[k][0], j1 = j + ds[k][1];
            if (i1 >= 0 && i1 < n && j1 >= 0 && j1 < m && !visited[i1][j1] && grid[i1][j1] && dist[i1][j1] > 1 + dist[i][j])
            {
                dist[i1][j1] = 1 + dist[i][j];
                pq.push({dist[i1][j1], {i1, j1}});
            }
        }
    }
    vi actions;
    visited = vvi(n, vi(m));
    auto dfs = [&](int i, int j, int d, auto &&dfs)-> bool{
        visited[i][j] = true;
        if(i == 0 || i == n - 1 || j== 0 || j == m - 1) return true;
        rep(k, 0, 4)
        {
            int i1 = i + ds[k][0], j1 = j + ds[k][1];
            if (i1 >= 0 && i1 < n && j1 >= 0 && j1 < m && !visited[i1][j1] && grid[i1][j1] && dist[i1][j1] > 1 + d)
            {
                actions.pb(k);
                if(dfs(i1, j1, d + 1, dfs))return true;
                actions.pop_back();
            }
        }
        return false;
    };
    bool res = dfs(a.f, a.s, 0, dfs);
    if(res){
        cout << "YES\n";
        cout << sz(actions) << nL;
        for(int i : actions){
            cout << dir[i];
        }
        cout << nL;
    }else{
        cout << "NO\n";
    }

    return 0;
}
