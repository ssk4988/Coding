#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vii = vector<pii>;
using vll = vector<pll>;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

void solve() {
    ll n, k; cin >> n >> k;
    map<ll, pll> dp; // sm, cnt for range [0, length)
    auto go = [&](ll start, ll length, auto &&go) -> pll {
        if(dp.count(length)) {
            auto [sm, cnt] = dp[length];
            sm += start * cnt;
            return {sm, cnt};
        }
        auto &[sm, cnt] = dp[length];
        if(length < k) {
            sm = 0, cnt = 0;
            return {sm, cnt};
        }
        if(length % 2 == 0){
            auto [sm1, cnt1] = go(0, length/2, go);
            auto [sm2, cnt2] = go(length/2, length/2, go);
            sm = sm1 + sm2, cnt = cnt1 + cnt2;
        } else {
            auto [sm1, cnt1] = go(0, length/2, go);
            auto [sm2, cnt2] = go(length/2+1, length/2, go);
            sm = sm1 + sm2, cnt = cnt1 + cnt2;
            cnt++;
            sm += length/2;
        }
        return {sm + start * cnt, cnt};
    };
    auto [sm, cnt] = go(1, n, go);
    cout << sm << "\n";
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc)
    solve();
    
    return 0;
}
