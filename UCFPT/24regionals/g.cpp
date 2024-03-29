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
    int m; cin >> m;
    vvi a(n, vi(m));
    rep(i, 0, n){
        string str; cin >> str;
        rep(j, 0, m){
            a[i][j] = str[j] - '0';
        }
    }
    a.insert(a.begin(), vi(m));
    n++;
    vector<int> last(m, n);
    vector<vi> next(n);
    for(int i = n - 1; i >= 0; i--){
        next[i] = last;
        rep(j, 0, m){
            if(a[i][j]){
                last[j] = i;
            }
        }
    }
    vvi bucket(n+1);
    vi ans(1 << m, n);
    ans[0] = 0;
    bucket[0].pb(0);
    rep(i, 0, n){
        for(int mask : bucket[i]){
            if(ans[mask] != i) continue;
            rep(j, 0, m){
                if((mask >> j) & 1) continue;
                if(next[i][j] < ans[mask | (1 << j)]){
                    ans[mask | (1 << j)] = next[i][j];
                    bucket[next[i][j]].pb(mask | (1 << j));
                }
            }
        }
    }
    int res = m;
    rep(i, 0, 1 << m){
        if(ans[i] == n) res = min(res, __builtin_popcount(i) - 1);
    }
    cout << res << "\n";

    return 0;
}
