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
        rep(i, 0, n) cin >> a[i];
        auto test = [&](ll lim) -> bool {
            ll cur = 0;
            vi rig(n, -1);
            int r = 0;
            vvi rem(n + 1);
            rep(l, 0, n){
                while(r < l || (r < n && cur + a[r] <= lim)) {cur += a[r]; r++;}
                rig[l] = r;
                rem[r].pb(l);
                cur -= a[l];
            }
            vector<vl> dp(n + 1, vl(2, 1e17));
            // dp[i][0] = did first i elements, last was unblocked
            // dp[i][1] = did first i elements, last was blocked
            dp[0][1] = 0; // consider a block at the start
            multiset<ll> inrange;
            rep(i, 0, n + 1){
                if(i > 0){
                    dp[i][1] = min(dp[i][1], min(dp[i-1][0], dp[i-1][1]) + a[i-1]);
                }
                if(sz(inrange)){
                    dp[i][0] = min(dp[i][0], *inrange.begin());
                }
                inrange.insert(dp[i][1]);
                // dp[i + 1][1] = min(dp[i + 1][1], min(dp[i][0], dp[i][1]) + a[i]);
                // if(rig[i] > i){
                //     dp[rig[i]][0] = min(dp[rig[i]][0], dp[i][1]);
                // }
                for(int j : rem[i]){
                    auto it = inrange.find(dp[j][1]);
                    if(it != inrange.end()){
                        inrange.erase(it);
                    }
                }
            }

            // rep(i, 0, n){
            //     if(cur + a[i] > lim){
            //         block += a[i];
            //         cur = 0;
            //     }
            //     else {
            //         cur += a[i];
            //     }
            // }
            return min(dp[n][0], dp[n][1]) <= lim;
        };
        ll x = 0;
        for(ll dif = 1LL << 52; dif > 0; dif /= 2){
            if(!test(x + dif))
                x += dif;
        }
        x++;
        cout << x << nL;
    }
    
    return 0;
}
