#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pi = pair<int, int>;
using pl = pair<ll, ll>;
using pd = pair<ld, ld>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vpi = vector<pi>;
using vpl = vector<pl>;
using vpd = vector<pd>;
using vvi = vector<vi>;

#define f first
#define s second
#define mp make_pair
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define nL "\n"

double dp[11][11][11];
ll choose[55][55];

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, d, c; cin >> n >> d >> c;
    vi a(c), b(c);
    rep(i, 0, c) {
        cin >> a[i]; a[i]--;
    }
    rep(i, 0, c) {
        cin >> b[i]; b[i]--;
    }
    vi cnt(4);
    rep(i, 0, n) {
        bool ina = find(all(a), i) != end(a);
        bool inb = find(all(b), i) != end(b);
        cnt[(ina << 1) | inb]++;
    }
    choose[0][0] = 1;
    rep(i, 0, 51) {
        rep(j, 0, i+1) {
            choose[i+1][j] += choose[i][j];
            choose[i+1][j+1] += choose[i][j];
        }
    }
    memset(dp, -1, sizeof dp);
    auto go = [&](int one, int two, int both, auto &&go) -> double {
        auto &res = dp[one][two][both];
        if(!isnan(res)) return res;
        if ((one == 0 || two == 0) && both == 0) return res = 0;
        res = 0;
        ll goodways = 0;
        rep(o, 0, min(one, d) + 1) {
            rep(t, 0, min(two, d - o) + 1) {
                rep(b, 0, min(both, d - o - t) + 1) {
                    int none = d - o - t - b;
                    if(none == d) continue;
                    ll ways = choose[one][o] * choose[two][t] * choose[both][b] * choose[n - one - two - both][none];
                    goodways += ways;
                    res += ways * go(one - o, two - t, both - b, go);
                }
            }
        }
        res /= choose[n][d];
        res += 1;
        res *= choose[n][d];
        res /= goodways;
        return res;
    };
    cout << fixed << setprecision(8) << go(cnt[1], cnt[2], cnt[3], go) << "\n";
    
    return 0;
}
