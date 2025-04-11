#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vl = vector<ll>;

#define sz(x) (int)x.size()
#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)

struct FT {
    vector<ll> s;
    FT(int n) : s(n) {}
    void update(int pos, ll dif) {
        for(; pos < sz(s); pos |= pos+1) s[pos] += dif;
    }
    ll query(int pos) {
        ll res = 0;
        for(; pos > 0; pos &= pos-1) res += s[pos-1];
        return res;
    }
    int lower_bound(ll sum) {
        if(sum <= 0) return -1;
        int pos = 0;
        for(int pw = 1 << 25; pw; pw >>= 1) {
            if(pos + pw <= sz(s) && s[pos+pw-1] < sum)
                pos += pw, sum -= s[pos-1];
        }
        return pos;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    ll n, k;
    cin >> n >> k;
    vl a(n);
    rep(i, 0, n) cin >> a[i];
    auto cnt = [&](ll x) -> ll {
        // count num subarrays with sum < x, or rank(x) in set of subarray sums
        // ll offset = n;
        ll pref = n; // offset by n to not have negative pref sums
        FT ft(2*n+5);
        ft.update(pref, 1);
        ll ans = 0;
        rep(i, 0, n) {
            pref += a[i] >= x ? 1 : -1;
            ans += ft.query(pref+1);
            ft.update(pref, 1);
        }
        ans = n * (n+1)/2 - ans;
        return ans;
    };
    // kth smallest median 
    // to find largest x where cnt(x) <= k-1
    ll ans = -1;
    for(ll dif = 1LL << 30; dif; dif /= 2) {
        if(cnt(ans+dif) <= k-1) ans += dif;
    }
    cout << ans << "\n";



    return 0;
}
