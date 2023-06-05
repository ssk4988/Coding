#include <bits/stdc++.h>
using namespace std;
using ll = long long;

typedef pair<int, int> pi;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<vi> vvi;
typedef vector<pi> vpi;
typedef long double ld;
typedef vector<ld> vd;
typedef vector<vd> vvd;

#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define nl '\n'
#define s second
#define f first
#define rep(i,a,b) for(int i = a; i < b; i++)
#define pb push_back

const int DEBUG = false;

int label(int id, int parity){
    return id * 2 + parity;
}
pi unlabel(int id){
    return {id / 2, id % 2};
}
vvi adj;

void connect(int id1, int id2){
    adj[id1].pb(id2);
    adj[id2].pb(id1);
}
int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m, k; cin >> n >> m >> k;
    vi c(n);
    rep(i, 0, n){
        cin >> c[i];
    }
    adj.resize(2 * n);
    rep(i, 0, m){
        int a, b; cin >> a >> b;a--,b--;
        int par = c[a] != c[b];
        connect(label(a, 0), label(b, 0 ^ par));
        connect(label(a, 1), label(b, 1 ^ par));
    }
    int bigval = 1e9;
    int ans = 0;
    rep(i, 0, n){
        priority_queue<pi, vpi, greater<pi>> pq;
        vi visited(2 * n), dist(2 * n, bigval);
        pq.push({0, label(i, 0)});
        dist[label(i, 0)] = 0;
        while(!pq.empty()){
            pi p = pq.top();
            pq.pop();
            if(visited[p.s]) continue;
            visited[p.s] = true;
            if(dist[p.s] == bigval) continue;
            for(int j : adj[p.s]){
                if(!visited[j] && dist[j] > dist[p.s] + 1){
                    dist[j] = dist[p.s] + 1;
                    pq.push({dist[j], j});
                }
            }
        }
        int diam = 0;
        rep(j, 0, n){
            int d0 = min(dist[label(j, 0)], dist[label(j, 1)]);
            int d1 = max(dist[label(j, 0)], dist[label(j, 1)]);
            // if(d1 == bigval){
            //     diam = 
            // }
            diam = max(diam, min((d1 - d0 + k) / 2 + d0, d0 + k));
            // diam = max(diam, 
            // max(min(k + dist[label(j, 0)], 
            //         k/2 + dist[label(j, 1)]), 
            //     min(k + dist[label(j, 1)], 
            //         k/2 + dist[label(j, 0)])));
            // if(diam == 54){
            //     cout << "bruH";
            // }
        }
        ans = max(ans, diam);
    }
    cout << ans << nl;

    return 0;
}
