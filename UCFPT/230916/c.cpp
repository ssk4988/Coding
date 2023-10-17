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

int n, m, k; 
vvi adj;
vi bfs(int source){
    int BAD = 1e7;
    vi dist(n, BAD);
    dist[source] = 0;
    queue<int> q;
    q.push(source);
    while(!q.empty()){
        int k = q.front(); q.pop();
        for(int k1 : adj[k]){
            if(dist[k1] == BAD){
                dist[k1] = 1 + dist[k];
                q.push(k1);
            }
        }
    }
    return dist;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cin >> n >> m >> k;
    adj.resize(n);
    vi worm(n);
    rep(i, 0, k){
        int a; cin >> a; a--;
        worm[a] = true;
    }
    rep(i, 0, m){
        int a, b; cin >> a >> b; a--, b--;
        adj[a].pb(b);adj[b].pb(a);
    }
    vi from0 = bfs(0);
    vi fromn = bfs(n - 1);
    ll numerator = 0;
    ll disttotel = INT_MAX;
    ll sumfromn = 0;
    rep(i, 0, n){
        if(worm[i]){
            sumfromn += fromn[i];
        }
    }
    vpl sols;
    sols.pb({from0[n - 1], 1});
    rep(i, 0, n){
        if(worm[i]){
            sols.pb({(k - 1) * from0[i] + sumfromn - fromn[i], k - 1});
        }
    }
    rep(i, 0, sz(sols)){
        ll g = __gcd(sols[i].f, sols[i].s);
        sols[i].f /= g;
        sols[i].s /= g;
    }
    sort(all(sols), [](pl &a, pl&b)->bool{ return a.f * b.s < b.f * a.s; });
    cout << sols[0].f << "/" << sols[0].s << nL;

    return 0;
}
