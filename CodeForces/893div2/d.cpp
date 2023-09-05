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
        int n, k; cin >> n >> k;
        string str; cin >> str;
        vi a(n);
        rep(i, 0, n) a[i] = str[i] == '1';
        vi pref(a);
        rep(i, 1, n) pref[i] += pref[i - 1];
        vector<vvi> ending(2, vvi(n, vi(n + 1))), starting(2, vvi(n, vi(n + 1)));
        rep(w, 1, n + 1){
            rep(l, 0, n){
                int r = l + w - 1;
                if(r >= n) break;
                int sum1 = pref[r] - (l ? pref[l - 1] : 0);
                int sum0 = w - sum1;
                ending[0][r][sum1] = max(ending[0][r][sum1], w);
                ending[1][r][sum0] = max(ending[1][r][sum0], w);
                starting[0][l][sum1] = max(starting[0][l][sum1], w);
                starting[1][l][sum0] = max(starting[1][l][sum0], w);
            }
        }
        rep(i, 0, 2){
            rep(j, 0, n){
                rep(l, 0, n + 1){
                    if(l)ending[i][j][l] = max(ending[i][j][l], ending[i][j][l - 1]);
                    if(j)ending[i][j][l] = max(ending[i][j][l], ending[i][j - 1][l]);
                }
            }
        }
        rep(i, 0, 2){
            for(int j = n - 1; j >= 0; j--){
                rep(l, 0, n + 1){
                    if(l)starting[i][j][l] = max(starting[i][j][l], starting[i][j][l - 1]);
                    if(j + 1 < n)starting[i][j][l] = max(starting[i][j][l], starting[i][j + 1][l]);
                }
            }
        }
        // best l0 for each l1
        vi best(n + 1, -1);
        rep(i, 0, n){
            rep(j, 0, k + 1){
                int l1 = ending[1][i][j];
                int l0 = i + 1 < n ? starting[0][i + 1][k - j] : 0;
                best[l0] = max(best[l0], l1);
                l0 = ending[0][i][j];
                l1 = i + 1 < n ? starting[1][i + 1][k - j] : 0;
                best[l0] = max(best[l0], l1);
            }
        }
        rep(i, 1, n + 1){
            int ans = 0;
            rep(j, 0, n + 1){
                if(best[j] == -1) continue;
                ans = max(ans, j * i + best[j]);
            }
            cout << ans << " ";
        }
        cout << nL;
    }
    
    return 0;
}
