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
    int l = 0, r = n;
    vector<vl> bs;
    while(true) {
        if(r-l == 1) {
            assert(a[l] == 0);
            break;
        }
        int m = (l+r)/2;
        ll sum_left = 0;
        rep(i, l, m) sum_left += a[i];
        ll sum_right = 0;
        rep(i, m, r) sum_right += a[i];
        ll rem = min(sum_left, sum_right);
        vl b(n);
        vii bounds = {{l, m}, {m, r}};
        pii leftover = {-1, -1};
        for(auto [x, y] : bounds)
        {
            ll c = -1;
            for(ll dif = 1LL << 42; dif; dif /= 2) {
                ll cur = c + dif;
                ll amt = 0;
                rep(i, x, y) amt += max(0LL, a[i] - cur);
                if(amt > rem) c = cur;
            }
            c++;
            ll crem = rem;
            rep(i, x, y) {
                crem -= max(0LL, a[i] - c);
                b[i] = max(0LL, a[i] - c);
                a[i] = min(a[i], c);
            }
            assert(crem >= 0);
            rep(i, x, y) {
                if(a[i] == c && crem > 0) {
                    a[i]--;
                    b[i]++;
                    crem--;
                }
            }
            bool done = true;
            rep(i, x, y) if(a[i]) done = false;
            if(!done) {
                assert(leftover.f == -1);
                leftover = {x, y};
            }
        }
        bs.pb(b);
        if(leftover.f == -1) break;
        tie(l, r) = leftover;
    }
    bool valid = true;
    rep(i, 0, n) if(a[i] > 0) valid = false;
    assert(valid);
    cout << sz(bs) << "\n";
    for(auto &b : bs) {
        for(auto &x : b) cout << x << " ";
        cout << "\n";
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
