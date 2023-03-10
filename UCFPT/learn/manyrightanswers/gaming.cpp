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
using pil = pair<int, ll>;
using vpil = vector<pil>;

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

using dt = pair<ll, pi>;

bool cmp(dt a, dt b){
    return a.f / a.s.f < b.f / b.s.f;
}
vector<dt> vals;
vector<vector<pil>> rowstuff;

vpil calcrow(ll n, int rows){
    int colsize = 0;
    vpil dp(100);
    // i is insert location
    rep(i, 2, 98){
        for(auto &p : rowstuff[rows]){
            if(i + p.f - 1 <= 97 && dp[i - 2].s + p.s <= n && dp[i - 2].s + p.s > dp[i + p.f - 1].s){
                dp[i + p.f - 1] = {i - 2, dp[i - 2].s + p.s};
            }
        }
    }
    return dp;
}

ll ways(vector<vector<char>> &grid){
    vvl ans(sz(grid), vl(sz(grid[0])));
    ans[0][0] = 1;
    rep(i, 0, sz(ans)){
        rep(j, 0, sz(ans[i])){
            if(grid[i][j] != '.') continue;
            if(i > 0) ans[i][j] += ans[i - 1][j];
            if(j > 0) ans[i][j] += ans[i][j - 1];
        }
    }
    return ans.back().back();
}
// 1000000000000000000
int main()
{
    // cin.tie(0)->sync_with_stdio(0);
    // cin.exceptions(cin.failbit);
    ll ncr[101][101];
    ll maxN = 1'000'000'000'000'000'005LL;
    rep(i, 0, 101){
        rep(j, 0, 101){
            ncr[i][j] = -1;
        }
    }
    ncr[0][0] = 1;
    rowstuff.resize(101);
    rep(i, 1, 101){
        rep(j, 0, i + 1){
            if(j < i && ncr[i - 1][j] == -1) continue;
            if(j > 0 && ncr[i - 1][j - 1] == -1) continue;
            ncr[i][j] = 0;
            if(j < i) ncr[i][j] += ncr[i - 1][j];
            if(j > 0) ncr[i][j] += ncr[i - 1][j - 1];
            if(ncr[i][j] > maxN){
                ncr[i][j] = -1;
                continue;
            }
            int i1 = i - j, i2 = j;
            i1++;i2++;
            if(i1 > 95 || i2 > 95) continue;
            vals.pb({ncr[i][j], {i1, i2}});
            rowstuff[i1].pb({i2, ncr[i][j]});
        }
    }
    // sort(all(vals), cmp);
    sort(all(vals));
    reverse(all(vals));
    int nc; cin >> nc;
    rep(cn, 0, nc){
        ll n; cin >> n;
        ll tmp = n;
        int rowsUsed = 0;
        vector<vector<char>> ans(100, vector<char>(100, '*'));
        rep(i, 0, 100){
            ans[i][0] = '.';
            ans[i][99] = '.';
        }
        vpi stuff;
        while(n > 0){
            vector<vpil> dp(100);
            vl maxdp(100);
            int bestrow = 1;
            rep(i, 2, 98){
                dp[i] = calcrow(n, i);
                for(pil v : dp[i]){
                    maxdp[i] = max(v.s, maxdp[i]);
                }
                if(maxdp[i] > maxdp[bestrow] && maxdp[i] / (ld) maxdp[bestrow] > 1.01){
                    bestrow = i;
                }
            }
            // cout << "use row " << bestrow << " to eliminate " << maxdp[bestrow] << ", from  " << n << " to " << (n - maxdp[bestrow]) << nL;
            n -= maxdp[bestrow];
            int bestidx = 0;
            rep(i, 1, 98){
                if(dp[bestrow][i].s > dp[bestrow][bestidx].s){
                    bestidx = i;
                }
            }
            int lastrow = rowsUsed + bestrow - 1;
            rep(j, bestidx, 100){
                ans[lastrow][j] = '.';
            }
            while(bestidx != 0){
                rep(i, 0, bestrow){
                    rep(j, dp[bestrow][bestidx].f + 2, bestidx + 1){
                        ans[rowsUsed + i][j] = '.';
                    }
                }
                bestidx = dp[bestrow][bestidx].f;
                ans[rowsUsed][bestidx+1] = '.';
                if(bestidx != 0){
                    ans[lastrow][bestidx + 1] = '.';
                }
            }
            rowsUsed += bestrow + 1;
        }
        assert(rowsUsed - 1 <= 100);
        // cout << "numrows : " << rowsUsed << nL;
        cout << 100 << " " << 100 << nL;
        rep(i, 0, 100){
            rep(j, 0, 100){
                cout << ans[i][j];
            }
            cout << nL;
        }
        assert(ways(ans) == tmp);
        // cout << "ways in this grid: " << ways(ans) << nL;
    }
    
    return 0;
}