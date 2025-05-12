#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;
using ll = long long;
using vl = vector<ll>;

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define bitat(x, b) (((x) >> (b)) & 1)

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m; cin >> n >> m;
    n += 2, m += 2;
    vector<string> grid(n, string(""));
    rep(i, 0, n) {
        rep(j, 0, m) grid[i] += '*';
    }
    vii starts;
    // bit on means raised
    vvi gobs(n, vi(m, -1)), gsw(n, vi(m, -1));
    vvi raised(n, vi(m));
    rep(i, 1, n-1) {
        string s; cin >> s;
        rep(j, 0, sz(s)) {
            grid[i][j+1] = s[j];
            if(s[j] == 'S') starts.push_back({i, j+1});
            if(tolower(s[j]) >= 'a' && tolower(s[j]) <= 'd') {
                int bit = tolower(s[j]) - 'a';
                if(tolower(s[j]) != s[j]) {
                    raised[i][j+1] = 1;
                }
                gobs[i][j+1] = bit;
            }
            if(s[j] >= '1' && s[j] <= '4') {
                gsw[i][j+1] = s[j] - '1';
            }
        }
    }
    // rep(i, 0, n) {
    //     cerr << grid[i] << endl;
    // }
    // r1, c1, r2, c2, mask
    using state = array<int, 5>;
    set<state> seen;
    queue<pair<int, state>> q;
    q.push(pair<int, state>{0, state{starts[0].first, starts[0].second, starts[1].first, starts[1].second, 0}});
    vi dr{1, 0, -1, 0}, dc{0, 1, 0, -1};
    while(sz(q)) {
        auto [d_u, st] = q.front(); q.pop();
        auto [r1, c1, r2, c2, mask] = st;
        if(grid[r1][c1] == 'E' && grid[r2][c2] == 'E') {
            cout << d_u << "\n";
            return 0;
        }
        if(seen.count(st)) continue;
        // cerr << d_u << " " << r1 << " " << c1 << " " << r2 << " " << c2 << " " << mask << endl;
        seen.insert(st);
        rep(k, 0, 4) {
            int rf1 = r1 + dr[k], cf1 = c1 + dc[k], rf2 = r2 + dr[k], cf2 = c2 + dc[k];
            if(grid[rf1][cf1] == '*' || grid[rf2][cf2] == '*') continue;
            if(grid[rf1][cf1] == '#') {
                tie(rf1, cf1) = tie(r1, c1);
            }
            else if(gobs[rf1][cf1] != -1 && (bitat(mask, gobs[rf1][cf1])^raised[rf1][cf1])) tie(rf1, cf1) = tie(r1, c1);
            if(grid[rf2][cf2] == '#') {
                tie(rf2, cf2) = tie(r2, c2);
            }
            else if(gobs[rf2][cf2] != -1 && (bitat(mask, gobs[rf2][cf2])^raised[rf2][cf2])) tie(rf2, cf2) = tie(r2, c2);
            if(pii{rf1, cf1} == pii{rf2, cf2}) continue;
            
            int mask1 = mask;
            if(gsw[rf1][cf1] != -1 && pii{r1, c1} != pii{rf1, cf1}) mask1 ^= 1 << gsw[rf1][cf1];
            if(gsw[rf2][cf2] != -1 && pii{r2, c2} != pii{rf2, cf2}) mask1 ^= 1 << gsw[rf2][cf2];
            if(gobs[rf1][cf1] != -1 && (bitat(mask1, gobs[rf1][cf1])^raised[rf1][cf1])) continue;
            if(gobs[rf2][cf2] != -1 && (bitat(mask1, gobs[rf2][cf2])^raised[rf2][cf2])) continue;
            q.push(pair<int, state>{d_u+1, state{rf1, cf1, rf2, cf2, mask1}});
        }
    }
    assert(false);
    return 0;
}
