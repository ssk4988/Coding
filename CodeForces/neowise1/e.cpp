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
        int n; cin >> n;
        string s; cin >> s;
        vi a(n);
        rep(i, 0, n) a[i] = s[i] == 'P';
        vi p = {-2, -1};
        ll ans = 0;
        vi res(n);
        rep(i, 0, n) {
            if(a[i] == 0) {
                p[i&1] += 2;
                ans += (i - p[i&1])/2;
                res[p[i&1]] = a[i];
            }
        }
        p = {0, 1};
        rep(i, 0, 2) while(p[i] < n) p[i] += 2;
        for(int i = n-1; i >= 0; i--) {
            if(a[i] == 1) {
                p[i&1] -= 2;
                ans += (p[i&1] - i)/2;
                res[p[i&1]] = a[i];
            }
        }
        ans /= 2;
        int b = 0;
        while(b < n && res[b] == 0) b++;
        res.erase(begin(res), begin(res)+b);
        while(sz(res) && res.back() == 1) res.pop_back();
        rep(i, 0, sz(res)/2) ans += i/2+1;
        cout << ans << "\n";
    }
    
    return 0;
}
