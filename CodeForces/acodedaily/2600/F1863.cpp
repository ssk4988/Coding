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
    vl pref(n+1);
    rep(i, 0, n) {
        cin >> a[i];
        pref[i+1] = pref[i] ^ a[i];
    }
    vl starts(n), ends(n), zstart(n), zend(n);
    vi ans(n);
    rep(i, 0, n){
        for(int j = n-1; j >= i; j--){
            bool works = (i == 0 && j == n-1);
            if(zstart[i] || zend[j]) works = true;
            ll mask = pref[i] ^ pref[j+1];
            if(mask && ((starts[i] & mask) || (ends[j] & mask))) works = true;
            if(works){
                if(i == j) ans[i] = 1;
                if(mask){
                    int bit = __lg(mask);
                    starts[i] |= 1LL << bit;
                    ends[j] |= 1LL << bit;
                } else zstart[i] = zend[j] = 1;
            }
        }
    }
    rep(i,0,n) cout << ans[i];
    cout << "\n";
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc) solve();
    
    return 0;
}
