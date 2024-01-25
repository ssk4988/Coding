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
        string s; cin >> s;
        vl dp(n + 1, LLONG_MAX);
        map<int, int> m;
        dp[0] = 0;
        m[0] = 0;
        ll pref = 0;
        rep(i, 1, n + 1){
            pref += s[i-1] == '+' ? 1 : -1;
            dp[i] = dp[i - 1] + 1;
            if(m.count(pref)){
                dp[i] = min(dp[i], dp[m[pref]]);
            }
            m[pref] = i;
        }
        cout << dp[n] << nL;
    }
    
    return 0;
}
