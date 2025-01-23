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

ll test(ll a, ll b, ll c) {
    return (a^b) + (b^c) + (a^c);
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        ll l, r; cin >> l >> r;
        ll base = 0;
        int pid = -1;
        for(int b = 1 << 29; b; b /= 2) {
            if((l & b) == 0 && (r & b)) {
                base += b;
                break;
                // pid = __lg(b)
            }
            if(l&b) base += b;
        }
        cout << base-1 << " " << base << " ";
        ll cur = l;
        while(cur == base-1 || cur == base) cur++;
        assert(min(base-1, cur) >= l && max(base, cur) <= r);
        cout << cur << "\n";
        // cout << test(base-1, base, cur) << "\n";
    }
    // cout << test(123, 121, 118) << " " << test(965321865, 375544086 , 12551794) << "\n";
    
    return 0;
}
