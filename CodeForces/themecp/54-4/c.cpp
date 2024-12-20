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

const ll mod = 998244353;
ll modpow(ll b, ll e) {
	ll ans = 1;
	for (; e; b = b * b % mod, e /= 2)
		if (e & 1) ans = ans * b % mod;
	return ans;
}

const int N = 255;
ll dp[N][N][N];

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    memset(dp, -1, sizeof dp);
    int n, k; cin >> n >> k;
    n--;
    auto go = [&](int left, int w, int freq, auto &&go) -> ll {
        if(left == 0) return 1;
        if(w > k) return 0;
        ll &ans = dp[left][w][freq];
        if(ans != -1) return ans;
        ans = 0;
        (ans += go(left, w+1, 0, go)) %= mod;
        ll term = modpow(k-w+1, n-left) * modpow(freq + 1, mod-2) % mod;
        (ans += term * go(left-1, w, freq+1, go)) %= mod;
        // cout << left << " " << w << " " << freq << " " << ans << endl;
        return ans;
    };
    ll ans = go(n, 1, 0, go);
    rep(i, 1, n+1){
        (ans *= i) %= mod;
    }
    cout << ans << "\n";
    
    return 0;
}
