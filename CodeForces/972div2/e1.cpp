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
    rep(cn, 0, nc) {
        int l, n, m; cin >> l >> n >> m;
        vi a(l);
        rep(i, 0, l) cin >> a[i], a[i]--;
        vvi grid(n, vi(m));
        rep(i, 0, n) {
            rep(j, 0, m) cin >> grid[i][j], grid[i][j]--;
        }
        vvi prv(n+1, vi(m+1)); // 1 if the last player win by moving here
        for(int i = l-1; i >= 0; i--) {
            vvi win(n+1, vi(m+1));
            for(int r = n-1; r >= 0; r--) {
                for(int c = m-1; c >= 0; c--) {
                    prv[r][c] += prv[r+1][c] + prv[r][c+1] - prv[r+1][c+1];
                }
            }
            for(int r = n-1; r >= 0; r--) {
                for(int c = m-1; c >= 0; c--) {
                    if(grid[r][c] == a[i] && (i == l-1 || prv[r+1][c+1] == 0)) {
                        win[r][c] = 1;
                        // cerr << "aindex " << i << " r " << r << " c " << c << " wins " << endl;
                    }
                }
            }
            swap(prv, win);
        }
        bool firstwin = false;
        rep(i, 0, n){
            rep(j, 0, m) {
                if(prv[i][j]) firstwin = true;
            }
        }
        cout << (firstwin ? "T" : "N") << "\n";
    }
    
    return 0;
}
