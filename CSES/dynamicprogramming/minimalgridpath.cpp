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
    int n; cin >> n;
    vector<string> grid(n);
    rep(i, 0, n) {
        cin >> grid[i];
    }
    string ans;
    vii pos;
    pos.pb(pii{0, 0});
    cout << grid[0][0];
    rep(i, 0, 2 * (n-1)) {
        char best = 'Z' + 1;
        for(auto [r, c] : pos) {
            if(r+1 < n) {
                best = min(best, grid[r+1][c]);
            }
            if(c+1<n) best = min(best, grid[r][c+1]);
        }
        cout << best;
        vii new_pos;
        for(auto [r,c] : pos) {
            if(r+1 < n && grid[r+1][c] == best) {
                new_pos.pb({r+1, c});
            }
            if(c+1<n && grid[r][c+1] == best) {
                new_pos.pb({r, c+1});
            }
        }
        sort(all(new_pos));
        new_pos.erase(unique(all(new_pos)), end(new_pos));
        pos = new_pos;
    }
    cout << "\n";

    
    return 0;
}
