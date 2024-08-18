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
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n; cin >> n;
        map<string, int> m;
        vi g(n), w(n);
        rep(i, 0, n){
            string s1, s2;
            cin >> s1 >> s2;
            if(!m.count(s1)) m[s1] = sz(m);
            if(!m.count(s2)) m[s2] = sz(m);
            g[i] = m[s1], w[i] = m[s2];
        }
        vvi adj(n, vi(n));
        rep(i, 0, n){
            rep(j, 0, n){
                if(g[i] == g[j] || w[i] == w[j]) adj[i][j] = true;
            }
        }
        vvi dp(n, vi(1 << n));
        queue<pair<int, int>> q;
        rep(i, 0, n){
            dp[i][1 << i] = true;
            q.push({i, 1 << i});
        }
        int ans = 1;
        while(sz(q)){
            auto [pre, mask] = q.front(); q.pop();
            ans = max(ans, __builtin_popcount(mask));
            rep(i, 0, n){
                if(adj[pre][i] && !dp[i][mask | (1 << i)] && ((mask >> i) & 1) == 0){
                    dp[i][mask | (1 << i)] = true;
                    q.push({i, mask | (1 << i)});
                }
            }
        }
        cout << (n - ans) << "\n";
    }
    
    return 0;
}