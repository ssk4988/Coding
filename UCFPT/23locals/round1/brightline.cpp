#include <bits/stdc++.h>
using namespace std;

#define sz(x) (int)x.size()
#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)

using ll = long long;
using pi = pair<int, int>;
using vi = vector<int>;
using vl = vector<ll>;
using vpi = vector<pi>;
using pl = pair<ll, ll>;
using vpl = vector<pl>;

#define pb push_back
#define f first
#define s second

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m; cin >>n >> m;
    vector<vpi> adj(n);
    rep(i, 0, m){
        int a, b, w; char c; cin >> a >> b >> c >> w;
        a--,b--;
        adj[a].pb({b, (c == 'b' ? 1 : -1) * w});
    }
    const ll BAD = LLONG_MAX;
    vl dist(n, BAD);
    dist[0] = 0;
    rep(t, 0, m + 5){
        rep(i, 0, n){
            if(dist[i] == BAD) continue;
            for(auto [j, w] : adj[i]){
                dist[j] = min(dist[j], dist[i] + w);
            }
        }
    }
    rep(i, 0, n){
        if(dist[i] < 0){
            cout << (i + 1) << "\n";
        }
    }

}
