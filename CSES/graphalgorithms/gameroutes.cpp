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
    vvi adj(n);
    rep(i, 0, m){
        int a, b; cin >> a >> b;a--,b--;
        adj[a].pb(b);
    }
    
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
    cout << solve(0, solve) << nL;
    
    return 0;
}