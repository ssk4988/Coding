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
        vi vs(a);
        sort(all(vs));
        vs.erase(unique(all(vs)), end(vs));
        rep(i, 0, l) a[i] = lower_bound(all(vs), a[i]) - begin(vs);
        vvi grid(n, vi(m));
        const int inf = 1e9;
        vvi highestocc(m, vi(sz(vs), -1));
        rep(i, 0, n) {
            rep(j, 0, m) {
                cin >> grid[i][j], grid[i][j]--;
                auto it = lower_bound(all(vs), grid[i][j]);
                if(it == end(vs) || *it != grid[i][j]) continue;
                else grid[i][j] = it - begin(vs);
                highestocc[j][grid[i][j]] = max(highestocc[j][grid[i][j]], i);
            }
        }
        vi prvwin(m, -1); // max row in each col where previous guy won
        for(int i = l-1; i >= 0; i--) {
            int elimrow = 0; // if row < elimrow ur cooked
            vi win(m, -1);
            for(int c = m-1; c >= 0; c--) {
                if(highestocc[c][a[i]] >= elimrow) win[c] = highestocc[c][a[i]];
                elimrow = max(elimrow, prvwin[c]);
            }
            swap(prvwin, win);
        }
        bool firstwin = false;
        rep(i, 0, m) {
            if(prvwin[i] != -1) firstwin = true;
        }
        cout << (firstwin ? "T" : "N") << "\n";
    }
    
    return 0;
}
