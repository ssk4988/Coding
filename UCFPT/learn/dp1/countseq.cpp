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

ll dp[1001];

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        string s1, s2;
        cin >> s1 >> s2;
        memset(dp, 0, sizeof dp);
        dp[0] = 1;
        vi c[26];
        for(int i = s2.length() - 1; i >= 0; i--){
            c[s2[i] - 'a'].pb(i + 1);
        }
        rep(i, 0, s1.length()){
            int c1 = s1[i] - 'a';
            for(auto a : c[c1]){
                dp[a] += dp[a - 1];
            }
        }
        cout << dp[s2.length()] << nL;
    }
    
    return 0;
}