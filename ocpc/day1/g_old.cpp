#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vl = vector<ll>;
using vvi = vector<vi>;

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++) 

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, m, k; cin >> n >> m >> k;

    vvi grid(n, vi(m));
    rep(i, 0, n) rep(j, 0, m)
        cin >> grid[i][j];

    vvi matching(1 << n, vi(m+1, -1));
    matching[0] = vi(m+1);
    for(int col = m-1; col >= 0; col--) {
        rep(mask, 1, 1 << n) {
            matching[mask][col] = matching[mask][col+1];
            rep(i, 0, n) {
                if(!((mask >> i)&1)) continue;
                if(matching[mask ^ (1 << i)][col+1] == -1) continue;
                matching[mask][col] = max(matching[mask][col], grid[i][col] + matching[mask ^ (1 << i)][col+1]);
            }
        }
    }
    vector ord(1 << n, vector(m+1, vi{}));
    for(int col = m-1; col >= 0; col--) {
        rep(mask, 0, 1 << n) {
            if(matching[mask][col] == -1) continue;
            auto cmp = [&](int a, int b) {
                int r1 = a / m, c1 = a % m;
                int r2 = b / m, c2 = b % m;
                return matching[mask ^ (1 << r1)][c1+1] + grid[r1][c1] > matching[mask ^ (1 << r2)][c2+1] + grid[r2][c2];
            };
            vi tmp;
            rep(i, 0, n) {
                if(!((mask >> i)&1)) continue;
                tmp.push_back(i * m + col);
            }
            sort(all(tmp), cmp);
            merge(all(tmp), all(ord[mask][col+1]), back_inserter(ord[mask][col]), cmp);
        }
    }
    // rep(mask, 0, 1 << n) {
    //     rep(col, 0, m) {
    //         cerr << "match " << mask << " " << col << " " << matching[mask][col] << endl;
    //         for(int v : ord[mask][col]) {
    //             cerr << (v/m) << "," << (v%m) << endl;
    //         }
    //     }
    // }

    auto calc = [&](int lim, bool build) -> pair<bool, vii> {
        using state = array<int, 3>;
        vector<vector<state>> q(n+1);
        q[0].push_back({(1 << n)-1, 0, 0});
        rep(u, 0, n) {
            for(auto [mask, col, cost] : q[u]) {
                for(int o : ord[mask][col]) {
                    if(sz(q[u+1]) >= k) break;
                    int r1 = o / m, c1 = o % m;
                    int cost1 = cost + grid[r1][c1];
                    if(cost1 + matching[mask ^ (1 << r1)][c1+1] < lim) break;
                    q[u+1].push_back({mask ^ (1 << r1), c1+1, cost1});
                }
            }
        }
        // rep(i, 0, n+1) {
        //     cerr << "lim=" << lim << " used " << i << " size " << sz(q[i]) << endl;
        //     for(auto [mask, col, cost] : q[i]){
        //         cerr << mask << " " << col << " " << cost << endl;
        //     }
        // }
        if(sz(q[n]) < k) return {false, vii{}};
        if(!build) return {true, vii{}};
        vii res;
        int mask = -1, col, cost;
        for(auto [a, b, c] : q.back()) if(c == lim) {
            tie(mask, col, cost) = tie(a, b, c);
        }
        assert(mask != -1);
        for(int u = n-1; u >= 0; u--) {
            bool found = false;
            // cerr << "at " << u << " " << mask << " " << col << " " << cost << endl;
            for(auto [mask1, col1, cost1] : q[u]) {
                if((mask1 & mask) != mask) continue;
                int r = __lg(mask1 ^ mask);
                // cerr << "trying " << mask1 << " " << col1 << " " << cost1 << endl;
                if(cost != cost1 + grid[r][col-1]) continue;
                found = true;
                res.push_back({r, col-1});
                mask = mask1;
                col = col1;
                cost = cost1;
                break;
            }
            assert(found);
        }
        return {true, res};
    };
    int ans = -1;
    for(int dif = 1 << 29; dif; dif /= 2) {
        auto [works, v] = calc(ans + dif, false);
        // cerr << ans+dif << " " << works << endl;
        if(works) ans += dif;
    }
    // ans++;
    auto [works, v] = calc(ans, true);
    if(!works){
        cout << "-1\n";
        return 0;
    }
    cout << ans << "\n";
    vi cols(n);
    for(auto [r, c] : v) {
        cols[r] = c;
        // cout << r << " " << c << "\n";
    }
    rep(i, 0, n){
        cout << cols[i]+1 << " ";
    }
    cout << "\n";


    return 0;
}
