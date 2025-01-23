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
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        ll l, r, g; cin >> l >> r >> g;
        ll ls = l / g * g;
        if(ls < l) ls += g;
        if(ls > r) {
            cout << "-1 -1\n";
            continue;
        }
        ll rs = r / g * g;
        array<ll, 4> best{-1, -ls, ls, ls};
        for(ll l1 = ls, cnt = 0; l1 <= r && cnt < 30; cnt++, l1 += g) {
            for(ll r1 = rs, cnt1 = 0; r1 >= l && cnt1 < 30; cnt1++, r1 -= g) {
                ll gc = __gcd(l1, r1);
                if(gc != g) continue;
                best = max(best, {abs(l1-r1), -l1, l1, r1});
            }
        }
        if(best[0] == -1){
            cout << "-1 -1\n";
            continue;
        }
        ll a = best[2], b = best[3];
        if(a > b) swap(a, b);
        cout << a << " " << b << "\n";
    }    
    
    return 0;
}
