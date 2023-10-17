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
        vl a(n);
        rep(i, 0, n){
            cin >> a[i];
        }
        const ll BAD = LLONG_MAX;
        ll curmex = 0;
        while(true){
            bool found = false;
            rep(i, 0, n){
                if(a[i] == curmex) found = true;
            }
            if(found) curmex++;
            else break;
        }
        vl freq(curmex + 5);
        rep(i, 0, n){
            if(a[i] < sz(freq)) freq[a[i]]++;
        }
        vl dp(curmex + 5, BAD);
        dp[curmex] = 0;
        for(ll i = sz(dp) - 1; i >= 0; i--){
            if(dp[i] == BAD) continue;
            for(ll j = 0;j < i; j++){
                dp[j] = min(dp[j], dp[i] + (i * (freq[j] - 1)) + j);
            }
        }
        cout << dp[0] << nL;
    }
    
    return 0;
}
