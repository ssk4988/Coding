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

ll MOD = 998244353;
ll mod(ll k){
    return (k % MOD + MOD) % MOD;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n; cin >> n;
        // ll w = 1, ans = 0;
        vi a(n+1);
        vl w(n+1), ans(n+1);
        w[1] = 1;
        rep(i, 1, n){
            cin >> a[i];
        }
        rep(i, 2, n+1){
            w[i] = mod((i - 1 - a[i-1]) * w[i - 1]);
        }
        rep(i, 1, n){
            ans[i] = mod(mod((i) * ans[i - 1]) + mod((a[i] == 0) * w[i]));
            cout << ans[i] << " ";
        }
        cout << nL;
    }
    
    return 0;
}
