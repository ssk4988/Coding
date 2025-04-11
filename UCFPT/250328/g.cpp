#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int)x.size()

using vi = vector<int>;
using ll = long long;
using vl = vector<ll>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;

random_device rdev;
mt19937 rng(rdev());

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    int maxcol = 10 + n * n / 100;
    int curcol = 1;
    vvi grid(n, vi(n, -1));
    map<pii, int> seen;
    map<int, int> freq;
    rep(i, 0, n){
        rep(j, 0, n) {
            int r = i / 10;
            int c = (r & 1) ? (j+5)/15 : j/15;
            if(!seen.count({r, c})) seen[{r, c}] = curcol++;
            int col = seen[{r, c}];
            grid[i][j] = col;
            freq[col]++;
        }
    }
    bool works = true;
    for(auto [key, val] : freq) if(val > 150 || key > maxcol) works = false;
    // rep(i, 0, n) {
    //     rep(j, 0, n) {
    //         set<int> used;
    //         rep(dr, -10, 11) {
    //             rep(dc, -10, 11) {
    //                 int i1 = i + dr, j1 = j + dc;
    //                 if(min(i1, j1) < 0 || max(i1, j1) >= n) continue;
    //                 if((i1-i) * (i1-i) + (j1-j) * (j1-j)) used.insert(grid[i1][j1]);
    //             }
    //         }
    //         if(sz(used) > 8) {
    //             works = false;
    //             cerr << i << "," << j << " " << grid[i][j] << " " << sz(used) << endl;
    //         }
    //     }
    // }
    // cerr << works << endl;
    rep(i, 0, n) {
        rep(j, 0, n){
            cout << grid[i][j] << " ";
        }
        cout << "\n";
    }
    assert(works);

    return 0;
}
