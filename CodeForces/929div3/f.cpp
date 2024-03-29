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
        int n, m; cin >> n >> m;
        vvi rock(n, vi(m));
        auto mod = [&](int k) -> int {
            return (k % n + n) % n;
        };
        rep(i, 0, n){
            rep(j, 0, m){
                cin >> rock[i][j];
            }
        }
        vvi t(n, vi(m, 2e9));
        queue<pi> q;
        t[0][0] = 0;
        q.push({0, 0});
        while(!q.empty()){
            auto [r, c] = q.front(); q.pop();
            if(!rock[(r+1)%n][c] && !rock[(r+2)%n][c] && t[(r+2)%n][c] == 2e9){
                t[(r+2)%n][c] = 1 + t[r][c];
                q.push({(r+2)%n, c});
            }
            if(c+1 < m && !rock[(r+1)%n][c+1] && t[(r+1)%n][c+1] == 2e9){
                t[(r+1)%n][c+1] = 1 + t[r][c];
                q.push({(r+1)%n, c+1});
            }
        }
        int ans = 2e9;
        rep(i, 0, n){
            ans = min(ans, t[i][m-1] + mod(i - mod(n-1 + t[i][m-1])));
        }
        if(ans == 2e9){
            ans = -1;
        }
        cout << ans << "\n";
    }
    
    return 0;
}
