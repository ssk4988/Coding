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
;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)
int MX = 3e5;
int SQRT = 2010;
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc;
    cin >> nc;
    rep(cn, 0, nc)
    {
        int n;
        cin >> n;
        vi a(n);
        rep(i, 0, n)
        {
            cin >> a[i];
        }
        rep(t, 0, SQRT)
        {
            rep(i, 0, n)
            {
                a[(i + 1) % n] = max(0, a[(i + 1) % n] - a[i]);
            }
        }
        vi ans;
        vi good(n), elim1(n);
        rep(i, 0, n)
        {
            if (a[i] && !a[(i + n - 1) % n])
                good[i] = true;
        }
        rep(i, 0, n)
        {
            if (good[(i + n - 1) % n])
            {
                elim1[i] = true;
            }
        }
        if (n >= 3)
        {
            rep(i, 0, n)
            {
                if (elim1[(i + n - 1) % n])
                {
                    if(a[i] && !a[(i + n - 1) % n]) good[i] = true;
                    else if(a[(i + n - 1) % n]) {
                        ll start = i == 1 ? a[0] : a[(i + n - 1) % n] - a[(i + n - 2) % n];
                        ll end = a[(i + n - 1) % n] % a[(i + n - 2) % n];
                        ll times = (start - end) / a[(i + n - 2) % n] + 1;
                        ll rem = (start + end) * times / 2;
                        good[i] = a[i] > rem;
                    }
                }
            }
        }
        rep(i, 0, n) if(good[i]) ans.pb(i);
        cout << sz(ans) << "\n";
        for (int i : ans)
            cout << i + 1 << " ";
        cout << "\n";
    }

    return 0;
}
