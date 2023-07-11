#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()

using ll = long long;
using vi = vector<int>;
using pi = pair<int, int>;

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, k; cin >> n >> k;
    vi a(n);
    rep(i, 0, n) cin >> a[i];
    int maxval = 2e9 + 1;
    int lo = 0, hi = maxval;
    while(lo < hi){
        int mid = lo + (hi - lo) / 2;
        // vi dp(n);
        // dp[0] = mid - (mid >= a[0]);
        int cur = mid;
        int lastchop = -2;
        rep(i, 0, n){
            if(cur >= a[i] && lastchop + 2 <= i){
                lastchop = i;
                cur--;
            }
        }
        // rep(i, 1, n){
        //     dp[i] = dp[i - 1];
        //     if(i - 2 >= 0 && dp[i - 2] >= a[i]) dp[i] = min(dp[i], dp[i - 2] - 1);
        // }
        if((mid - cur) >= k){
            hi = mid;
        } else lo = mid + 1;
    }
    if(lo == maxval) lo = -1;
    cout << lo << "\n";
}