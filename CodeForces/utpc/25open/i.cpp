#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vl = vector<ll>;

#define sz(x) (int)x.size()
#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vl a(n);
    rep(i, 0, n){
        cin >> a[i];
    }
    sort(all(a));
    ll mex = 0;
    ll ans = 0;
    vl dups;
    ll dupsum = 0;
    rep(i, 0, n) {
        if(a[i] < mex) {
            // dups.push_back(a[i]);
            dupsum += a[i];
            continue;
        }
        if(a[i] == mex) {
            mex++;
            continue;
        }
        ans += (a[i] - mex) * mex;
        a[i] = mex;
        mex++;
    }
    // sort(all(dups));
    ans += dupsum * mex;
    for(ll curmex = mex; curmex > 1; curmex--) {
        ans += curmex;
        ans += (curmex-1) * (curmex-2);
    }
    cout << ans << "\n";

    return 0;
}
