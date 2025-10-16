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
    int n; cin >> n;
    vl a(n);
    rep(i, 0, n) cin >> a[i];
    {

        ll sum = accumulate(all(a), 0LL);
        ll mx = *max_element(all(a));
        if(sum % 2 == 1 || 2 * mx > sum) {
            cout << "-1\n";
            return;
        }
    }
    {
        ll sum_left = 0;
        ll sum_right = accumulate(all(a), 0LL);
        pair<ll, int> bestsplit{1e18, -1};
        rep(i, 0, n) {
            bestsplit = min(bestsplit, {abs(sum_left - sum_right), i});
            sum_left += a[i];
            sum_right -= a[i];
        }
        auto [_, m] = bestsplit;
        sum_left = 0;
        sum_right = 0;
        rep(i, 0, m) sum_left += a[i];
        rep(i, m, n) sum_right += a[i];
        ll rem = min(sum_left, sum_right);
        ll leftover = max(sum_left, sum_right) - rem;
        vl b1(a);
        vl b2(n);
        pii rng = sum_left > sum_right ? pii{0, m} : pii{m, n};
        ll hl = leftover/2;
        rep(i, rng.f, n) {
            ll amt = min(hl, a[i]);
            hl -= amt;
            b1[i] -= amt;
            b2[i] += amt;
        }
        hl = leftover/2;
        for(int i = rng.s-1; i >= 0; i--) {
            ll amt = min(hl, a[i]);
            hl -= amt;
            b1[i] -= amt;
            b2[i] += amt;
        }
        for(auto &b : {b1, b2}) {
            ll sm = accumulate(all(b), 0LL);
            bool works = false;
            ll cur = 0;
            rep(i, 0, n) {
                cur += b[i];
                if(cur * 2 == sm) works = true;
            }
            assert(works);
        }
        cout << (leftover ? 2 : 1) << "\n";
        rep(i, 0, n){
            cout << b1[i] << " ";
        }
        cout << "\n";
        if(leftover) {
            rep(i, 0, n) {
                cout << b2[i] << " ";
            }
            cout << "\n";
        }
    }
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        solve();
    }
    
    return 0;
}
