#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
using ll = long long;
using pi = pair<int, int>;
using vi = vector<int>;
#define f first
#define s second

const ll MOD = 1e9 + 7;
ll mod(ll k) {
    return k % MOD;
}

int main() {
    freopen("rooks.in", "r", stdin);
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        ll n, m, k; cin >> n >> m >> k;
        vector<pi> cs(k);
        set<int> xs, ys;
        rep(i, 0, k){
            cin >> cs[i].f >> cs[i].s;
            xs.insert(cs[i].f);
            ys.insert(cs[i].s);
        }
        int minrooks = max(sz(xs), sz(ys)), other = min(sz(xs), sz(ys));
        int dim = sz(xs) < sz(ys) ? n : m;
        map<int, int> rlx, rly;
        for(int i : xs) rlx[i] = sz(rlx);
        for(int i : ys) rly[i] = sz(rly);

        vector<vector<ll>> dp(minrooks + 1, vector<ll>(1 + other));
        dp[0][0] = 1;
        rep(i, 0, minrooks){
            rep(j, 0, 1 + other){
                dp[i + 1][j] = mod(dp[i + 1][j] + mod(dp[i][j] * (dim - other + j)));
                if(j + 1 <= other){
                    dp[i + 1][j + 1] = mod(dp[i + 1][j + 1] + mod(dp[i][j] * (other - j)));
                }
            }
        }
        cout << "Case " << (cn + 1) << ": " << minrooks << " " << dp[minrooks][other] << "\n";
    }
}
