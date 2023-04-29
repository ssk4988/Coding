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
    int n, m, k; cin >> n >> m >> k;
    vector<vpl> adj(n);
    rep(i, 0,m ){
        int a, b; ll c; cin >> a >> b >> c;a--,b--;
        adj[a].pb({b, c});
    }
    vector<multiset<ll>> dist(n);
    vi processed(n);
    priority_queue<pl, vpl, greater<pl>> pq;
    dist[0].insert(0);
    pq.push({0, 0});
    while(!pq.empty()){
        pl p = pq.top(); pq.pop();
        auto [d, node] = p;
        if(processed[node] >= k) continue;
        processed[node]++;
        for(pl &e : adj[node]){
            ll newdist = d + e.s;
            if(dist[e.f].size() < k || *(dist[e.f].rbegin()) > newdist){
                if(dist[e.f].size() >= k) dist[e.f].erase(prev(dist[e.f].end()));
                dist[e.f].insert(newdist);
                pq.push({newdist, e.f});
            }
        }
    }
    for(ll i : dist[n - 1]){
        cout << i << " ";
    }
    cout << nL;

    
    return 0;
}