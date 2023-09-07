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
    int n, x; cin >> n >> x;
    vi dp(x + 1, INT_MIN);
    dp[0] = 0;
    vi hs(n), ss(n), ks(n);
    rep(i, 0, n) cin >> hs[i];
    rep(i, 0, n) cin >> ss[i];
    rep(i, 0, n) cin >> ks[i];
    rep(i, 0, n){
        // cout << "book " << i << nL;
        int h = hs[i], s = ss[i], k = ks[i];
        vpi upd;
        rep(j, 0, h){
            deque<pi> dq;
            for(int v = j, idx = 0; v <= x; v += h, idx++){
                while(dq.size() && dq.front().s < v - k * h) dq.pop_front();
                if(dq.size()){
                    auto [val, previdx] = dq.front();
                    upd.pb({v, val + s * idx});
                }
                if(dp[v] != INT_MIN){
                    pi nex = {dp[v] - idx * s, v};
                    while(dq.size() && dq.back() < nex) dq.pop_back();
                    dq.push_back(nex);
                }
            }
        }
        for(auto [idx, val] : upd){ 
            dp[idx] = max(dp[idx], val);
            // cout << "dp[" << idx << "] is now " << dp[idx] << nL;
        }
    }
    int ans = 0;
    rep(i, 0, x + 1) ans = max(ans, dp[i]);
    cout << ans << nL;
    
    return 0;
}