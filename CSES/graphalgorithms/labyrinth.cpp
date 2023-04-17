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
    int n, m; cin >> n >> m;
    vvi grid(n, vi(m));
    pi a, b;
    rep(i, 0, n){
        string str; cin >> str;
        rep(j, 0, m){
            grid[i][j] = str[j] != '#';
            if(str[j] == 'A') a= {i,j};
            if(str[j] == 'B') b = {i,j};
        }
    }
    vvi ds = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    vvi dist(n, vi(m, INT_MAX));
    vvi visited(n, vi(m));
    priority_queue<pair<int, pi>, vector<pair<int, pi>>, greater<pair<int, pi>>> pq;
    string dir = "DRUL";
    
    dist[a.f][a.s] = 0;
    pq.push({0, a});
    while(!pq.empty()){
        auto p = pq.top();pq.pop();
        auto [i,j] = p.s;
        if(visited[i][j]) continue;
        visited[i][j] = true;
        rep(k, 0, 4){
            int i1 = i + ds[k][0], j1 = j + ds[k][1];
            if(i1 >= 0 && i1 < n && j1 >= 0 && j1 < m && !visited[i1][j1] && grid[i1][j1] && dist[i1][j1] > 1 + dist[i][j]){
                dist[i1][j1] = 1 + dist[i][j];
                pq.push({dist[i1][j1],{i1,j1}});
            }
        }
    }
    cout << (visited[b.f][b.s] ? "YES" : "NO") << nL;
    if(visited[b.f][b.s]){
        // cout << dist[b.f][b.s] << nL;
        vpi path;
        vi actions;
        path.pb(b);
        while(path.back() != a){
            auto [i,j] = path.back();
            rep(k, 0, 4){
                int i1 = i + ds[k][0], j1 = j + ds[k][1];
                if(i1 >= 0 && i1 < n && j1 >= 0 && j1 < m && grid[i1][j1] && dist[i1][j1] == dist[i][j] - 1){
                    path.pb({i1,j1});
                    actions.pb((k + 2) % 4);
                    break;
                }
            }
        }
        reverse(all(actions));
        cout << sz(actions) << nL;
        rep(i, 0, sz(actions)){
            cout << dir[actions[i]];
        }
        cout << nL;
    }
    
    return 0;
}
