#include <bits/stdc++.h>
using namespace std;

using ld = long double;
const ld eps = 1e-5;
int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int l, w, h; cin >> l >> w >> h;
    ld x, y, a; cin >> x >> y >> a;
    ld x1 = x + h * cos(a * acosl(-1) / 180), y1 = y + h * sin(a * acosl(-1) / 180);
    // cout << x1 << " " << y1 << "\n";
    bool works = -eps <= x1 && x1 <= w + eps && -eps <= y1 && y1 <= l + eps;
    cout << (works ? "YES" : "NO") << "\n";


    return 0;
}
