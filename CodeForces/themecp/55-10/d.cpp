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
        int n, w, h, k; cin >> n >> k >> w >> h;
        map<pii, int> pref;
        int x = 0, y = 0;
        string s; cin >> s;
        for(char c : s) {
            if(c == 'U') {
                y++;
            } else if(c == 'D') y--;
            else if(c == 'R') x++;
            else x--;
            x = (x + 2 * w) % (2 * w);
            y = (y + 2 * h) % (2 * h);
            pref[{x, y}]++;
        }
        ll cx = 0, cy = 0;
        ll ans = 0;
        rep(i, 0, k) {
            ll tx = (2 * w - cx) % (2 * w), ty = (2 * h - cy) % (2 * h);
            ans += pref[{tx, ty}];
            cx += x; cy += y;
            cx %= 2 * w; cy %= 2 * h;
            cx = (cx + 2 * w) % (2 * w);
            cy = (cy + 2 * h) % (2 * h);
        }
        cout << ans << "\n";
    }
    
    return 0;
}
