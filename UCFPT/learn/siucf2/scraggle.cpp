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



int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    int w; cin >> w;
    set<string> trie;
    set<string> done;
    vector<string> dict(w);
    rep(i, 0, w) {
        cin >> dict[i];
        rep(j, 0, sz(dict[i])) trie.insert(dict[i].substr(0, j+1));
        done.insert(dict[i]);
    }
    rep(cn, 0, nc) {
        vi val(26);
        rep(i, 0, 26) cin >> val[i];
        vvi let(4, vi(4));
        vvi mult(4, vi(4));
        rep(i, 0, 4){
            rep(j, 0, 4) cin >> let[i][j];
        }
        rep(i, 0, 4){
            rep(j, 0, 4) cin >> mult[i][j];
        }
        vector<string> grid(4);
        rep(i, 0, 4) cin >> grid[i];
        vvi used(4, vi(4));
        int ways = 0;
        int ans = 0;
        string s;
        auto dfs = [&](int r, int c, int wmult, int cur, string &s, auto &&dfs) -> void {
            s += grid[r][c];
            if(!trie.count(s)) {
                s.pop_back();
                return;
            }
            ways++;
            wmult *= mult[r][c];
            cur += val[grid[r][c]-'a'] * let[r][c];
            if(done.count(s)) ans = max(ans, wmult * cur);
            used[r][c] = true;
            rep(dr, -1, 2) {
                rep(dc, -1, 2) {
                    int r1 = r + dr, c1 = c + dc;
                    if(min(r1, c1) < 0 || max(r1, c1) >= 4) continue;
                    if(used[r1][c1]) continue;
                    if(min(r1, c1) < 0 || max(r1, c1) >= 4) continue;
                    dfs(r1, c1, wmult, cur, s, dfs);
                }
            }
            used[r][c] = false;
            s.pop_back();
        };
        rep(i, 0, 4) {
            rep(j, 0, 4) {
                dfs(i, j, 1, 0, s, dfs);
            }
        }

        // cout << ways << "\n";
        cout << ans << "\n";
    }
    
    return 0;
}
