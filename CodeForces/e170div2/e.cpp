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

const ll MOD = 998244353;

vl conv(vl &a, vl &b) {
    vl res(sz(a) + sz(b) - 1);
    rep(i, 0, sz(a)){
        rep(j, 0, sz(b)){
            (res[i+j] += a[i] * b[j]) %= MOD;
        }
    }
    res.resize(sz(a));
    return res;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m; cin >> n >> m;
    vector<vl> dp(m+1, vl(m+1, -1));
    auto go = [&](int left, int over, auto &&go) -> ll {
        auto &ans = dp[left][over];
        if(ans != -1) return ans;
        if(left == 0) return ans=(over == 0);
        ans = 0;
        if(over) (ans += go(left-1, over-1, go)) %= MOD;
        if (over < m) (ans += go(left-1, over+1, go)) %= MOD;
        return ans;
    };
    vl base(m+1);
    rep(i, 0, m+1) base[i] = go(m, i, go);
    vl other(base);
    reverse(all(other));
    rep(i, 0, n-1) other = conv(other, base);
    cout << other.back() << "\n";
    
    
    return 0;
}
