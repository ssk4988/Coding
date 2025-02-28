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

pii solve(vi grid, int n, int m) {
    int tog = 0;
    rep(i, 1, n) {
        rep(j, 0, m) {
            if((grid[i-1] >> j)&1) {
                grid[i-1] ^= 1 << j;
                tog++;
                if(i+1 < n) {
                    grid[i+1] ^= 1 << j;
                }
                if(j) grid[i] ^= 1 << (j-1);
                if(j+1 < m) grid[i] ^= 1 << (j+1);
            }
        }
    }
    return {grid.back(), tog};
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    
    int nc; cin >> nc;
    vi val(1 << 25), cnt(1 << 25);
    rep(cn, 0, nc) {
        int r, c; cin >> r >> c;
        vi grid(r);
        rep(i, 0, r) {
            string s; cin >> s;
            rep(j, 0, c) {
                grid[i] ^= (s[j] == '1') << j;
            }
        }
        rep(i, 0, r) {
            string s; cin >> s;
            rep(j, 0, c) {
                grid[i] ^= (s[j] == '1') << j;
            }
        }
        auto [base, basetog] = solve(grid, r, c);
        vi changes(c);
        vi delta(c);
        rep(i, 0, c) {
            if(i) grid[0] ^= 1 << (i-1);
            if(i+1<c) grid[0] ^= 1 << (i+1);
            if(r >= 2) grid[1] ^= 1 << i;
            auto [chbase, chtog] = solve(grid, r, c);
            chbase ^= base;
            chtog -= basetog;
            changes[i] = chbase;
            delta[i] = chtog;
            cout << changes[i] << " " << delta[i] << endl;
            if(i) grid[0] ^= 1 << (i-1);
            if(i+1<c) grid[0] ^= 1 << (i+1);
            if(r >= 2) grid[1] ^= 1 << i;
        }
        pii ans = {1e9, 0};
        bool seen = false;
        val[0] = 0;
        rep(mask, 0, 1 << c) {
            int bits = __builtin_popcount(mask);
            if(mask) {
                int bit = __lg(mask & -mask);
                val[mask] = val[mask ^ (1 << bit)];
                val[mask] ^= changes[bit];
                cnt[mask] = cnt[mask ^ (1 << bit)];
                cnt[mask] += delta[bit];
            }
            int cur = base ^ val[mask];
            int togans = basetog + cnt[mask];
            if(cur == 0 && !seen) {
                // seen = true;
                // vi grid2(grid);
                // rep(i, 0, c) {
                //     if((mask >> i) & 1) {
                //         if(i) grid2[0] ^= 1 << (i-1);
                //         if(i+1<c) grid2[0] ^= 1 << (i+1);
                //         if(r >= 2) grid2[1] ^= 1 << i;
                //     }
                // }
                // auto [last, tog] = solve(grid2, r, c);
                ans = min(ans, {bits + togans, mask});
                // break;
            }
        }
        if(ans.first == 1e9) ans.first = -1;
        cout << ans.first << "\n";
    }

    return 0;
}
