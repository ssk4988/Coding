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

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    int k; cin >> k;
    vector<string> grid(n);
    vvi has(n, vi(n));
    vi made(k);
    rep(i, 0, n) {
        cin >> grid[i];
        vvi bucket(k);
        rep(j, 0, n) {
            bucket[grid[i][j] - 'A'].pb(j);
        }
        rep(j, 0, k) {
            if(made[j]) continue;
            rep(a, 0, sz(bucket[j])) {
                rep(b, a+1, sz(bucket[j])) {
                    int l = bucket[j][a], r = bucket[j][b];
                    if((has[l][r] >> j)&1) {
                        made[j] = 1;
                        break;
                    }
                }
            }
            rep(a, 0, sz(bucket[j])) {
                rep(b, a+1, sz(bucket[j])) {
                    int l = bucket[j][a], r = bucket[j][b];
                    has[l][r] |= 1 << j;
                }
            }
        }
    }
    rep(i, 0, k) {
        cout << (made[i] ? "YES" : "NO") << "\n";
    }
    
    return 0;
}
