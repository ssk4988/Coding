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
        int n, q; cin >> n >> q;
        map<ll, ll> ans;
        vl x(n);
        rep(i, 0, n) cin >> x[i];
        rep(i, 0, n){
            ans[ll(i+1) * (n-i)-1]++;
            if(i)ans[ll(i) * (n - i)] += (x[i] - x[i-1] - 1);
        }
        rep(i, 0, q){
            ll k;cin >> k;
            cout << ans[k] << " ";
        }
        cout << "\n";
    }
    
    return 0;
}