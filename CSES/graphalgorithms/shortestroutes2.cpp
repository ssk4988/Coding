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
using vvl = vector<vl>;

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
    int n, m, q;
    cin >> n >> m >> q;
    ll BAD = 1'000'000'000'000'000LL;
    vvl adj(n, vl(n)), dist(n, vl(n, BAD));
    rep(i, 0, m){
        int a, b, c; cin >> a >> b >> c;
        a--,b--;
        adj[a][b] = adj[b][a] = c;
        dist[a][b] = dist[b][a] = min(adj[a][b], dist[a][b]);
    }
    rep(i, 0, n){
        dist[i][i] = 0;
    }
    rep(k, 0, n){
        rep(i, 0, n){
            rep(j, 0, n){
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
    rep(i, 0, q){
        int a,b; cin >> a >> b;a--,b--;
        if(dist[a][b] == BAD){
            cout << "-1\n";
            continue;
        }
        cout << dist[a][b] << nL;
    }
    
    return 0;
}