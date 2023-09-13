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
        int n; cin >> n;
        vector<vector<bool>> grid(n, vector<bool>(n)), starts(n, vector<bool>(n)), ends(n, vector<bool>(n));
        rep(i, 0, n){
            string str; cin >> str;
            rep(j, 0, n){
                grid[i][j] = str[j] - '0';
            }
        }
        int ans = 0;
        vector<bool> updatestart(n), updateend(n);
        rep(i, 0, n){
            int cur = 0, pref = 0;
            rep(j, 0, n) updatestart[j] = updateend[j] = false;
            rep(j, 0, n){
                pref ^= starts[i][j] ^ ends[i][j];
                cur = pref ^ grid[i][j];
                if(cur){
                    ans++;
                    // cout << "use at " << i << " " << j << " with pref " << pref << " " << nL;
                    updatestart[j] = !updatestart[j];
                    if(j + 1 < n) updateend[j + 1] = !updateend[j + 1];
                }
            }
            if(i + 1 < n){
                rep(j, 0, n){
                    starts[i + 1][max(0, j - 1)] = updatestart[j] ^ starts[i][j] ^ starts[i + 1][max(0, j - 1)];
                    if(j + 1 < n){
                        ends[i + 1][j + 1] = updateend[j] ^ ends[i][j] ^ ends[i + 1][j + 1];
                    }
                }

            }
        }
        cout << ans << nL;
    }
    
    return 0;
}