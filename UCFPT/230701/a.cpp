#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
using ll = long long;
using pi = pair<int, int>;
using vi = vector<int>;
using ld = long double;

int main() {
    freopen("zeriba.in", "r", stdin);
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n; cin >> n;
        vi a(n);
        int sum = 0, longest = 0;
        rep(i, 0, n) {
            cin >> a[i];
            sum += a[i];
            longest = max(a[i], longest);
        }
        if(longest * 2 >= sum){
            cout << "Case " << (cn + 1) << ": can't form a convex polygon\n";
            continue;
        }
        ld eps = 1e-6;
        ld lo = ld(longest) / 2, hi = 1e9;
        while(fabs(hi - lo) > eps){
            ld mid = (lo + hi) / 2;
            ld ang = 0;
            rep(i, 0, n){
                ang += acosl((ld(a[i]) * a[i] - 2 * mid * mid) / -2 / mid / mid);
            }
            if(ang <= 2 * acosl(-1)){
                hi = mid;
            }
            else lo = mid;
        }
        cout << "Case " << (cn + 1) << ": " << fixed << setprecision(4) << lo << "\n";
    }
}
