#include <bits/stdc++.h>
using namespace std;

using ld = long double;
using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;
using vd = vector<ld>;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
const ld eps = 1e-8;
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n;
    ll w;
    cin >> n >> w;
    vd xs(n), ys(n);
    vd slope(n);
    rep(i, 0, n)
    {
        cin >> xs[i] >> ys[i];
    }
    rep(i, 0, n - 1)
    {
        slope[i] = (ys[i + 1] - ys[i]) / (xs[i + 1] - xs[i]);
    }
    cout << fixed << setprecision(9);
    ld window = 0;
    if (xs[n - 1] - xs[0] <= w)
    {
        rep(i, 0, n - 1)
        {
            window += (ys[i + 1] + ys[i]) / 2 * (xs[i + 1] - xs[i]);
        }
        window /= w;
        cout << window << "\n";
        return 0;
    }
    int l = 0, r = 0;
    ld vl = xs[0], vr = xs[0] + w;
    while (r + 1 < n && xs[r + 1] <= vr + eps)
    {
        window += (ys[r + 1] + ys[r]) / 2 * (xs[r + 1] - xs[r]);
        r++;
    }
    window += (ys[r] + ys[r] + slope[r] * (vr - xs[r])) / 2 * (vr - xs[r]);
    ld ans = window / w;
    while (true)
    {
        while (r + 1 < n && xs[r + 1] <= vr + eps)
        {
            r++;
        }
        while (l + 1 < n && xs[l + 1] <= vl + eps)
        {
            l++;
        }
        if (r == n - 1 || l == n - 1)
            break;
        ld adv = min(xs[l + 1] - vl, xs[r + 1] - vr);
        if (ys[r] + slope[r] * (vr - xs[r]) > ys[l] + slope[l] * (vl - xs[l]) && ys[r] + slope[r] * (vr + adv - xs[r]) < ys[l] + slope[l] * (vl + adv - xs[l]))
        {
            ld window1 = window;
            ld adv1 = ((ys[r] + slope[r] * (vr - xs[r])) - (ys[l] + slope[l] * (vl - xs[l]))) / (slope[l] - slope[r]);
            window1 += (ys[r] + slope[r] * (vr - xs[r]) + ys[r] + slope[r] * (vr + adv1 - xs[r])) / 2 * adv1;
            window1 -= (ys[l] + slope[l] * (vl - xs[l]) + ys[l] + slope[l] * (vl + adv1 - xs[l])) / 2 * adv1;
            ans = max(ans, window1 / w);
        }
        window += (ys[r] + slope[r] * (vr - xs[r]) + ys[r] + slope[r] * (vr + adv - xs[r])) / 2 * adv;
        window -= (ys[l] + slope[l] * (vl - xs[l]) + ys[l] + slope[l] * (vl + adv - xs[l])) / 2 * adv;
        ans = max(ans, window / w);
        vl += adv, vr += adv;
    }
    cout << ans << "\n";

    return 0;
}
