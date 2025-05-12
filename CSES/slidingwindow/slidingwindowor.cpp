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

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, k; cin >> n >> k;
    ll x, a, b, c; cin >> x >> a >> b >> c;
    vi v;
    v.pb(x);
    rep(i, 0, n-1) {
        v.pb((a * v.back() + b) % c);
    }
    ll ans = 0;
    vi freq(30);
    vii st1, st2;
    rep(i, 0, n) {
        st1.pb({v[i], v[i] | (sz(st1) ? st1.back().s : 0)});
        if(i >= k) {
            if(sz(st2)) st2.pop_back();
            else {
                while(sz(st1)) {
                    auto [x, mn] = st1.back();
                    st2.pb({x, x | (sz(st2) ? st2.back().s : 0)});
                    st1.pop_back();
                }
                st2.pop_back();
            }
        }
        int res = 0;
        if(sz(st1)) res |= st1.back().s;
        if(sz(st2)) res |= st2.back().s;
        if(i >= k-1) ans ^= res;
    }
    cout << ans << "\n";
    
    return 0;
}
