#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;
using ll = long long;
using vl = vector<ll>;

#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int)x.size()
const int mod = 1e9+7;
const int inv2 = (mod+1)/2;
const int N = 16;
int dp[1 << N][N][2][2];
int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int nc; cin >> nc;
    rep(cn, 0, nc) {
        int n; cin >> n;
        vi s(n), t(n);
        rep(i, 0, n) {
            cin >> s[i] >> t[i];
            s[i]--, t[i]--;
        }
        int allmask = (1 << n)-1;
        rep(mask, 0, 1 << n) {
            rep(last, 0, n) {
                rep(i, 0, 2) {
                    rep(j, 0, 2) dp[mask][last][i][j] = mask == allmask ? (j ? inv2 : 1) : -1;
                }
            }
        }
        for(int mask = allmask-1; mask >= 0; mask--) {
            rep(last, 0, n) {
                rep(rev, 0, 2) {
                    rep(flip, 0, 2) {
                        auto &ans = dp[mask][last][flip][rev];

                        ans = 0;
                        int prvl = flip ? t[last] : s[last];
                        int prvr = flip ? s[last] : t[last];
                        rep(i, 0, n) {
                            if((mask >> i)&1) {
                                continue;
                            }
                            rep(flip1, 0, 2) {
                                if(flip1 && t[i] == s[i]) continue;
                                int l = flip1 ? t[i] : s[i];
                                int r = flip1 ? s[i] : t[i];
                                if(l != prvr) continue;
                                bool rev2 = rev && (mask == 0 || (prvl == r && prvr == l));
                                (ans += dp[mask ^ (1 << i)][i][flip1][rev2]) %= mod;
                                // if(mask == 0 || s[i] == last) {
                                //     (ans += go(mask ^ (1 << i), t[i], go)) %= mod;
                                // }
                                // if((mask == 0 || t[i] == last) && s[i] != t[i]) {
                                //     (ans += go(mask ^ (1 << i), s[i], go)) %= mod;
                                // }
                            }
                        }
                    }
                }
            }
        }

        // vector dp(1 << n, vector(n, vector(2, vi(2, -1))));

        // auto go = [&](int mask, int last, int flip, int rev, auto &&go) -> int {
        //     if(mask == allmask) {
        //         return rev ? inv2 : 1;
        //     }
        //     auto &ans = dp[mask][last][flip][rev];
        //     if(ans != -1) return ans;
        //     ans = 0;
        //     int prvl = flip ? t[last] : s[last];
        //     int prvr = flip ? s[last] : t[last];
        //     rep(i, 0, n) {
        //         if((mask >> i)&1) {
        //             continue;
        //         }
        //         rep(flip1, 0, 2) {
        //             if(flip1 && t[i] == s[i]) continue;
        //             int l = flip1 ? t[i] : s[i];
        //             int r = flip1 ? s[i] : t[i];
        //             if(l != prvr) continue;
        //             bool rev2 = rev && (mask == 0 || (prvl == r && prvr == l));
        //             (ans += go(mask ^ (1 << i), i, flip1, rev2, go)) %= mod;
        //             // if(mask == 0 || s[i] == last) {
        //             //     (ans += go(mask ^ (1 << i), t[i], go)) %= mod;
        //             // }
        //             // if((mask == 0 || t[i] == last) && s[i] != t[i]) {
        //             //     (ans += go(mask ^ (1 << i), s[i], go)) %= mod;
        //             // }
        //         }
        //     }
        //     // cerr << cn << " "<<mask << " " << last << " " << ans << endl;
        //     return ans;
        // };
        cout << (2*dp[0][0][0][1])%mod << "\n";
        // cout << (2*go(0, 0, 0, 1, go))%mod << "\n";
    }

    return 0;
}
// ab|bc|cd
// ba|cb|dc
// a=c, b=d
