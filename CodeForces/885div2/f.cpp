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
    int n;
    cin >> n;
    vi a(n);
    rep(i, 0, n)
    {
        cin >> a[i];
    }
    int ans = 0;
    // rep(_, 0, 20)
    // {
        vi x(a);
        // rep(i, 0, n) x[i] = (a[i] >> _) & 1;
        int cur = 0;
        for (int dif = n/2; dif; dif /= 2)
        {
            vi x2(x);
            rep(i, 0, n) x2[i] ^= (x[(i + dif) % n]);
            if (accumulate(all(x2), 0))
            {
                x = x2;
                cur += dif;
            }
        }
        if (accumulate(all(x), 0)) cur++;
        ans = max(ans, cur);
    // }
    cout << ans << "\n";

    return 0;
}
