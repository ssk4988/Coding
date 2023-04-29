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
    vvi adj(n);
    rep(i, 0, m){
        int a, b; cin >> a >> b;a--,b--;
        adj[a].pb(b);
    }
    int BLANK = INT_MIN;
    int low = -1e8;
    vi dist(n, BLANK);
    auto solve = [&](int cur, auto &&solve)->int{
        if(dist[cur] != BLANK) return dist[cur];
        if(cur == n - 1){
            dist[cur] = 0;
            return dist[cur];
        }
        dist[cur] = 0;
        for(int i : adj[cur]){
            dist[cur] = max(dist[cur], 1 + solve(i, solve));
        }
        if(dist[cur] == 0 && cur != n - 1) dist[cur] = low;
        return dist[cur];
    };
    solve(0, solve);
    if(dist[0] >= 0){
        vi path;
        path.pb(0);
        while(dist[path.back()] > 0){
            for(int i : adj[path.back()]){
                if(dist[i] == dist[path.back()] - 1){
                    path.pb(i);
                    break;
                }
            }
        }
        cout << sz(path) << nL;
        for(int i : path) cout << (i + 1) << " ";
        cout << nL;
    }
    else{
        cout << "IMPOSSIBLE\n";
    }

    
    return 0;
}