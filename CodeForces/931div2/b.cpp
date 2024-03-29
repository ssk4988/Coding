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
    int bucket = 162000;
    vi dp(bucket+1, 1e9);
    dp[0] = 0;
    vi coins = {1, 3, 6, 10, 15};
    rep(i, 0, bucket+1){
        for(int c : coins){
            if(i >= c) dp[i] = min(dp[i], dp[i - c] + 1);
        }
    }
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n; cin >> n;
        ll ans = n / bucket * (bucket / 15) + dp[n % bucket];
        cout << ans << nL;
    }
    
    return 0;
}
