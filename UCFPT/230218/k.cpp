#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef pair<int, int> pi;
typedef long long ll;
typedef vector<ll> vl;
typedef vector<pi> vii;
typedef vector<vi> vvi;

#define rep(i,a,b) for(int i = a; i < b; i++)
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)
#define nl '\n'
#define pb push_back
#define se second
#define fi first

const int DEBUG = false;

int n, m;

struct best{
    int minpath = INT_MAX, maxpath = INT_MIN;
    int prevmin = -1, prevmax = -1;
    int index;
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    cin >> n >> m;
    vi dist(n, INT_MAX);
    vector<vector<pi>> adj(n);
    rep(i, 0, m){
        int a, b, w; cin >> a >> b >> w;
        a--,b--;
        adj[a].pb({b, w});
        adj[b].pb({a, w});
    }
    dist[0] = 0;
    vector<bool> visited(n);
    priority_queue<pi, vector<pi>, greater<pi>> pq;
    pq.push({dist[0], 0});
    while(!pq.empty()){
        pi p = pq.top(); pq.pop();
        if(visited[p.se]) continue;
        visited[p.se] = true;
        for(auto &pa : adj[p.se]){
            if(dist[pa.fi] > dist[p.se] + 1){
                dist[pa.fi] = dist[p.se] + 1;
                pq.push({dist[pa.fi], pa.fi});
            }
        }
    }
    for(int i = 0; i < n; i++){
        vector<pi> cop(adj[i]);
        adj[i].clear();
        for(auto &p : cop){
            if(dist[p.fi] == dist[i] + 1){
                adj[i].pb(p);
            }
        }
    }
    vector<vector<best>> b(n, vector<best>(2));
    rep(i, 0, n){
        b[i][0].index = b[i][1].index = i;
    }
    queue<int> q;
    visited = vector<bool>(n, false);
    q.push(0);
    while(!q.empty()){
        int i = q.front(); q.pop();
        if(visited[i]) continue;
        visited[i] = true;
        for(pi &p : adj[i]){
            best &th = b[p.fi][0];
            // int newmin = min(p.se, b[i][0].minpath == INT_MAX)
            if(th.minpath > min(p.se, b[i][0].minpath)){
                th.minpath = min(p.se, b[i][0].minpath);
                th.prevmin = i;
                q.push(p.fi);
            }
            if(th.maxpath < max(p.se, b[i][0].maxpath)){
                th.maxpath = max(p.se, b[i][0].maxpath);
                th.prevmax = i;
                q.push(p.fi);
            }
        }
    }
    visited = vector<bool>(n, false);
    vector<vector<pi>> radj(n);
    rep(i, 0, n){
        for(auto &p : adj[i]){
            auto [j, c] = p;
            radj[j].pb({i, c});
        }
    }
    adj = radj;
    q.push(n - 1);
    while(!q.empty()){
        int i = q.front(); q.pop();
        if(visited[i]) continue;
        visited[i] = true;
        for(pi &p : adj[i]){
            best &th = b[p.fi][1];
            if(th.minpath > min(p.se, b[i][1].minpath)){
                th.minpath = min(p.se, b[i][1].minpath);
                th.prevmin = i;
                q.push(p.fi);
            }
            if(th.maxpath < max(p.se, b[i][1].maxpath)){
                th.maxpath = max(p.se, b[i][1].maxpath);
                th.prevmax = i;
                q.push(p.fi);
            }
        }
    }
    int bestrange = 0, bestindex = 0;
    rep(i, 1, n - 1){
        int range = max(b[i][0].maxpath - b[i][1].minpath, b[i][1].maxpath - b[i][0].minpath);
        if(range > bestrange){
            bestrange = range;
            bestindex = i;
        }
    }
    vi buildback;
    buildback.pb(bestindex);
    bool minleft = b[bestindex][1].maxpath - b[bestindex][0].minpath > b[bestindex][0].maxpath - b[bestindex][1].minpath;
    while(buildback.back() != 0){
        buildback.pb(minleft ? b[buildback.back()][0].prevmin : b[buildback.back()][0].prevmax);
    }
    reverse(all(buildback));
    while(buildback.back() != n - 1){
        buildback.pb(minleft ? b[buildback.back()][1].prevmax : b[buildback.back()][1].prevmin);
    }
    cout << dist[n - 1] << nl;
    // buildback.pb(n - 1);
    rep(i, 0, sz(buildback)){
        cout << (buildback[i] + 1) << " \n"[i + 1 == sz(buildback)];
    }

    return 0;
}
