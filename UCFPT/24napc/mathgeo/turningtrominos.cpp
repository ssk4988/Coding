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
using vll = vector<pll>;;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)


// layers start at 0
int solve(int layer, ll x, ll y) {
    if(layer == 0) return 0;
    ll dim = 1LL << layer;
    ll small = dim / 2;
    ll xd = x / small, yd = y / small;
    set<pll> s0{{0, 0}, {1, 0}, {0, 1}}, s3{{1, 1}, {2, 1}, {1, 2}},
        s1{{0, 2}, {0, 3}, {1, 3}}, s2{{2, 0}, {3, 0}, {3, 1}};
    pll c = {xd, yd};
    // if(layer <= 2) cout << layer << " " << x << " " << y << "\n";
    if(s0.count(c)) return solve(layer-1, x, y);
    if(s3.count(c)) return solve(layer-1, x-small, y-small);
    if(s1.count(c)) return (1 + solve(layer-1, dim-1 - (y-dim), x)) % 4;
    if(s2.count(c)) return (3 + solve(layer-1, y, dim-1 - (x-dim))) % 4;
    return -1;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        ll x, y; cin >> x >> y;
        // cout << x << " " << y << ":\n";
        cout << solve(61, x, y) << "\n";
    }
    
    return 0;
}
