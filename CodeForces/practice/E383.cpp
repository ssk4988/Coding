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
    int n; cin >> n;
    vl sub(1 << 24);
    rep(i, 0, n) {
        set<int> v;
        string s; cin >> s;
        for(char c : s) v.insert(c - 'a');
        vi o(all(v));
        rep(mask, 1, 1 << sz(o)){
            int actmask = 0;
            rep(j, 0, sz(o)) {
                if((mask >> j) & 1) actmask ^= 1 << o[j];
            }
            sub[actmask] += __builtin_popcount(mask) & 1 ? 1 : -1;
        }
    }
    rep(bit, 0, 24) {
        rep(mask, 0, sz(sub)) {
            if((mask >> bit) & 1) sub[mask] += sub[mask - (1 << bit)];        
        }
    }
    ll ans = 0;
    rep(mask, 0, sz(sub)) {
        ans ^= sub[mask] * sub[mask];
    }
    cout << ans << "\n";
    
    return 0;
}
