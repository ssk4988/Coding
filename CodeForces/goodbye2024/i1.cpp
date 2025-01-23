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
    ll tot = accumulate(all(a), 0LL);
    vector<array<ll, 3>> rng;
    rng.pb({0, 1, 0});
    if(tot > 0) rng.pb({1, tot+1, 1});
    for (ll d : a) {
        assert(sz(rng) < 10);
        vector<array<ll, 3>> rng2;
        ll mn = 1e18;
        vector<array<ll, 3>> events;
        for(auto [l, r, v] : rng){
            l += d, r += d;
            l = clamp(l, 0LL, tot+1);
            r = clamp(r, 0LL, tot+1);
            if(l < r) events.pb({l, v, 1}), events.pb({r, v, -1}), mn = min(mn, 1+v);
        }
        multiset<ll> vs;
        ll prv = 0;
        events.pb({0, mn, 1});
        events.pb({tot+1, mn, -1});
        sort(all(events));
        for(auto [x, v, t] : events) {
            if(x != prv) {
                ll val = *begin(vs);
                if(sz(rng2) && rng2.back()[2] == val) rng2.back()[1] = x;
                else rng2.pb({prv, x, val});
            }
            if(t == 1) vs.insert(v);
            else if(t == -1) vs.erase(vs.find(v));
            prv = x;
        }
        swap(rng, rng2);
    }
    ll ans = 1e18;
    for(auto [l, r, v] : rng) {
        if(l <= tot && tot+1 <= r) ans = v;
    }
    cout << ans+n << "\n";
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
