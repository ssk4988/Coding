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

ll MOD = 1e9 + 7;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m; cin >> n >> m;
    vector<vpl> wadj(n);
    vvi adj(n);
    rep(i, 0, m){
        int a, b; ll w; cin >> a >> b >> w;
        a--,b--;
        wadj[a].pb({b, w});
    }
    vl dist(n, LLONG_MAX);
    dist[0] = 0;
    vi visited(n);
    priority_queue<pl, vpl, greater<pl>> pq;
    pq.push({0, 0});
    while(!pq.empty()){
        pl p = pq.top();pq.pop();
        if(visited[p.s])continue;
        visited[p.s] = true;
        for(pl &p1 : wadj[p.s]){
            if(dist[p1.f] > dist[p.s] + p1.s){
                dist[p1.f] = dist[p.s] + p1.s;
                pq.push({dist[p1.f], p1.f});
            }
        }
    }
    rep(i, 0, n){
        for(auto &p : wadj[i]){
            if(dist[i] + p.s == dist[p.f]){
                adj[i].pb(p.f);
            }
        }
    }
    cout << dist[n - 1] << " ";
    int BLANK = -1;
    vl ways(n, BLANK);
    auto solve = [&](int cur, auto && solve)->ll{
        if(ways[cur] != BLANK) return ways[cur];
        if(cur == n - 1) return (ways[cur] = 1);
        ways[cur] = 0;
        for(int i : adj[cur]){
            ways[cur] = (ways[cur] + solve(i, solve)) % MOD;
        }
        return ways[cur];
    };
    cout << solve(0, solve) << " ";
    vi dist1 = vi(n, BLANK);
    auto solve3 = [&](int cur, auto &&solve3)->int{
        if(dist1[cur] != BLANK) return dist1[cur];
        if(cur == n - 1){
            dist1[cur] = 0;
            return dist1[cur];
        }
        dist1[cur] = 1e8;
        for(int i : adj[cur]){
            dist1[cur] = min(dist1[cur], 1 + solve3(i, solve3));
        }
        return dist1[cur];
    };
    solve3(0, solve3);
    cout << dist1[0] << " ";
    BLANK = INT_MIN;
    int low = -1e8;
    dist1 = vi(n, BLANK);
    auto solve2 = [&](int cur, auto &&solve2)->int{
        if(dist1[cur] != BLANK) return dist1[cur];
        if(cur == n - 1){
            dist1[cur] = 0;
            return dist1[cur];
        }
        dist1[cur] = 0;
        for(int i : adj[cur]){
            dist1[cur] = max(dist1[cur], 1 + solve2(i, solve2));
        }
        if(dist1[cur] == 0 && cur != n - 1) dist1[cur] = low;
        return dist1[cur];
    };
    solve2(0, solve2);
    cout << dist1[0] << nL;
    
    return 0;
}