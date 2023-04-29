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
    int n; cin >> n;
    ll x; cin >> x;
    vl w(n);
    rep(i, 0, n){
        cin >> w[i];
    }
    vpi dp(1 << n, {n + 1, 0});
    dp[0] = {1, 0};
    rep(i, 0, 1 << n){
        rep(j, 0, n){
            if((i & (1 << j)) == 0){
                dp[i | (1 << j)] = min(dp[i | (1 << j)], {dp[i].f + (dp[i].s + w[j] > x), (dp[i].s + w[j] > x ? w[j] : dp[i].s + w[j])});
            }
        }
    }
    cout << dp[(1 << n) - 1].f << nL;
    
    return 0;
}