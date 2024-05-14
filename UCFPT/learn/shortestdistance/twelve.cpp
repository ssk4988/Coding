#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vii = vector<pii>;
using vll = vector<pll>;;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vvi d(n, vi(n));
    rep(i, 0, n){
        rep(j, 0, n){
            cin >> d[i][j];
        }
    }
    rep(k, 0, n){
        rep(i, 0, n){
            rep(j, 0, n) d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
        }
    }
    int q; cin >> q;
    rep(i, 0, q){
        int s, e, t; cin >> s >> e >> t;
        int ans = 0;
        rep(j, 0, n) if((j & 1) && d[s][j] + d[j][e] + 134 <= t) ans++;
        cout << ans << "\n";
    }
    
    return 0;
}
