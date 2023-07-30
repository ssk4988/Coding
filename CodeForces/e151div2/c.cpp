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
    int nc; cin >> nc;
    rep(cn, 0, nc){
        string s; cin >> s;
        int n = sz(s);
        vi a(n);
        rep(i, 0, n) a[i] = s[i] - '0';
        vvi nex(n + 1, vi(10));
        vi seen(10, n + 1);
        for(int i = n; i >= 0; i--){
            rep(j, 0, 10){
                nex[i][j] = seen[j];
            }
            if(i > 0){
                seen[a[i - 1]] = i;
            }
        }
        int m; cin >> m;
        string l, r; cin >> l >> r;
        vi la(m), ra(m);
        rep(i, 0, m){
            la[i] = l[i] - '0';
            ra[i] = r[i] - '0';
        }
        vvi dp(n + 2, vi(m + 1));
        dp[0][0] = true;
        rep(i, 0, n + 1){
            rep(j, 0, m){
                if(!dp[i][j]) continue;
                for(int k = la[j]; k <= ra[j]; k++){
                    dp[nex[i][k]][j + 1] = true;
                }
            }
        }
        bool reachend = false;
        rep(i, 0, m + 1) reachend |= dp[n + 1][i];
        cout << (reachend ? "YES" : "NO") << nL;
    }
    
    return 0;
}
