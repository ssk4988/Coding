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
using vvl = vector<vl>;

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

ll MOD = 1e9+7;
ll mod(ll k){
    return k % MOD;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n, k; cin >> n >> k;
        vi a(n);
        vvi occ(n);
        vi revocc(n);
        vi prevocc(n, -1);
        rep(i, 0, n) {
            cin >> a[i];
            a[i]--;
            revocc[i] = occ[a[i]].size();
            occ[a[i]].pb(i);
        }
        vi jump(n, -1);
        vi backward(n, -1);
        rep(i, 0, n){
            int cnt = 0;
            rep(j, i, n){
                if(a[j] == a[i]){
                    cnt++;
                    if(cnt == 2){
                        prevocc[j] = i;
                    }
                    if(cnt >= k){
                        jump[i] = j;
                        backward[j] = i;
                        break;
                    }
                }
            }
        }
        int prefmax = 0;
        vi best(n);
        rep(i, 0, n){
            if(i > 0){
                best[i] = max(best[i], best[i - 1]);
            }
            rep(j, 0, i + 1){
                if(jump[j] != -1 && jump[j] <= i){
                    best[i] = max(best[i], 1 + (j > 0 ? best[j - 1] : 0));
                }
            }
        }
        int opt = best.back();
        if(opt == 0 || k == 1){
            cout << 1 << nL;
            continue;
        }
        vvl dp(opt * k + 1, vl(n));
        vvl prefdp(opt * k + 1, vl(n));
        rep(i, 0, n){
            dp[0][i] = 1;
        }
        rep(i, 0, n){
            // prefdp[0][i] = mod(dp[0][i] + (i > 0 ? prefdp[0][i - 1] : 0));
            prefdp[0][i] = 1;
        }
        rep(i, 1, opt * k + 1){
            rep(j, 0, n){
                if(i % k != 1){
                    if(prevocc[j] != -1) dp[i][j] = prefdp[i - 1][prevocc[j]];
                }
                else{
                    if(j > 0) dp[i][j] = prefdp[i - 1][j - 1];
                    else if(i == 1) dp[i][j] = 1;
                }
            }
            rep(j, 0, n){
                if(i % k == 0){
                    prefdp[i][j] = mod(dp[i][j] + (j > 0 ? prefdp[i][j - 1] : i - 1 == 0));
                }
                else{
                    prefdp[i][j] = dp[i][j];
                    if(prevocc[j] != -1){
                        prefdp[i][j] = mod(prefdp[i][j] + prefdp[i][prevocc[j]]);
                    }
                }
            }
        }
        // vector<vvl> prefocc(opt + 1, vvl(n));
        // dp[0][0] = prefdp[0][0] = 1;
        // // prefocc[0][a[0]].pb(1);
        // rep(i, 1, n){
        //     prefdp[0][i] = prefdp[0][i - 1] + dp[0][i];
        // }
        // rep(i, 0, n){
        //     prefocc[0][i].pb(1);
        // }
        // rep(i, 1, opt + 1){
        //     rep(j, 0, n){
        //         if(backward[j] == -1) continue;
        //         if(i == 1){
        //             if(revocc[j] >= k - 1){
        //                 dp[i][j] = 1 + revocc[j] - (k - 1);
        //             }
        //         }
        //         else{
        //             if(revocc[j] >= k - 1){
        //                 dp[i][j] = prefocc[i - 1][a[j]][revocc[j] - (k - 1)];
        //             }
        //         }
        //         // dp[i][jump[j]] = mod(dp[i][jump[j]] + mod((j > 0 ? prefdp[i - 1][j - 1] : i - 1 == 0)));
        //     }
        //     rep(j, 0, n){
        //         prefdp[i][j] = dp[i][j];
        //         if(j > 0) prefdp[i][j] = mod(prefdp[i][j] + prefdp[i][j - 1]);
        //     }
        //     prefocc[i][a[0]].pb(0);
        //     rep(j, 1, n){
        //         prefocc[i][a[j]].pb(mod(prefdp[i][j - 1] + 
        //             (prefocc[i][a[j]].size() == 0 ? 0 : prefocc[i][a[j]].back())));
        //     }
        // }
        // cout << "max path length: " << opt << nL;
        cout << prefdp.back().back() << nL;
    }
    
    return 0;
}