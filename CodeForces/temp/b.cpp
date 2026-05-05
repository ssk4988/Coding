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

int jmp(int x) {
    int z = -1;
    for(int dif = 1 << 29; dif; dif /= 2) {
        int cur = z + dif;
        if(abs(cur*2-x) <= abs(x-cur)) z = cur;
    }
    z++;
    return z;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    // rep(x, 2, 100) cerr << x << " " << jmp(x) << " " << (2 * x + 3) / 3 << endl;
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        int x, y; cin >> x >> y;
        // if(y == 1) {
        //     cout << (x == 1 ? 0 : -1) << "\n";
        //     continue;
        // }
        // if((x == 2 || x == 3) && y < x) {
        //     cout << "-1\n";
        //     continue;
        // }
        int ans = 0;
        while(x > y && (x > 3)) {
            int z = (2 * x + 3) / 3;
            // while(abs(z*2-x) <= abs(x-z)) z++;
            if(z <= y) z = y;
            // cerr << x << " " << y << " " << z << endl;
            x = z;
            ans++;
        }
        while(2*x <= y) {
            ans++;
            // cerr << x << " " << y << " " << 2*x << endl;
            x *= 2;
        }
        if(x < y) ans++, x = y;
        if(x > y) cout << "-1\n";
        else cout << ans << "\n";
    }
    
    return 0;
}
