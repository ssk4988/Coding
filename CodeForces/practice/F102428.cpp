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
const ll MOD = 1e9 + 7;
inline ll mod(ll k){
    return k % MOD;
}

inline ll mod1(ll k){
    return (k % MOD + MOD) % MOD;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int s, b; cin >> s >> b;
    vector<vl> dp(s + 1, vl(b + 1));
    vector<vl> pref(s + 1, vl(b + 1));
    vector<vl> pref2(s + 1, vl(b + 1));
    rep(i, 0, s + 1){
        rep(j, 0, b + 1){
            // if(i >= j) continue;
            if(i == j){
                dp[i][j] = 1;
            }
            else if(i > j){}
            else{
                dp[i][j] = mod1(pref2[i][j-i] - mod(pref[i][j-i] * (s - i)));
                // rep(l, 0, i + 1){
                //     if(i-l > j-i) continue;

                //     dp[i][j] = mod(dp[i][j] + mod((l + 1) * dp[i-l][j-i]));
                // }
            }
            pref2[i][j] = mod((s + 1 - i) * dp[i][j]);
            pref[i][j] = dp[i][j];
            if(i > 0) pref2[i][j] += pref2[i-1][j];
            if(i > 0) pref[i][j] += pref[i-1][j];
        }
    }
    cout << dp[s][b] << "\n";
    
    return 0;
}
