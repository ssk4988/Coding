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
    string str; cin >> str;
    int n = sz(str);
    vl dp(n, 1);
    vi nxt(2, n);
    for(int i = n-1; i >= 0; i--){
        rep(j, 0, 2) if(nxt[j] != n) dp[i] += dp[nxt[j]];
        nxt[str[i] - '0'] = i;
    }
    nxt = vi(2, n);
    ll ans = 0;
    rep(i, 0, n){
        cout << i << " " << dp[i] << "\n";
        if(nxt[str[i] - '0'] == n){
            nxt[str[i] - '0'] = i;
            ans += dp[i];
        }
    }
    cout << ans << "\n";
    
    return 0;
}
