#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pi = pair<int, int>;
using pl = pair<ll, ll>;
using pd = pair<ld, ld>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vpi = vector<pi>;
using vpl = vector<pl>;
using vpd = vector<pd>;
using vvi = vector<vi>;

#define f first
#define s second
#define mp make_pair
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define nL "\n"

const int N = 12;
const int K = 705;

int n, x;
int a[N];
int dp[1 << N][N][K];


int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cin >> n >> x;
    int mx = 0;
    rep(i, 0, n){
        cin >> a[i];
        mx = max(mx, a[i]);
    }
    rep(i, 0, n){
        if(a[i] == mx) continue;
        int score = (mx+1 - a[i]) * n;
        if(score >= K) continue;
        dp[1 << i][i][score] = 1;
    }
    rep(mask, 0, 1 << n) {
        int used = __builtin_popcount(mask);
        rep(last, 0, n) {
            if(((mask >> last) & 1) == 0) continue;
            rep(score, 0, K) {
                if(dp[mask][last][score] == 0) continue;
                rep(next, 0, n) {
                    if((mask >> next) & 1) continue;
                    int newscore = score + max(0, 1 + a[last] - a[next]) * (n - used);
                    if(newscore < K){
                        dp[mask ^ (1 << next)][next][newscore] += dp[mask][last][score];
                    }
                }
            }
        }
    }
    int ans = 0;
    rep(last, 0, n){
        rep(k, 0, x+1){
            ans += dp[(1 << n)-1][last][k];
            // if(dp[(1 << n)-1][last][k]) {

            // }
        }
    }
    cout << ans << "\n";
    return 0;
}
