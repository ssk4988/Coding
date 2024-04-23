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

const int MAX_N = 1001;
const int D = 10;

int a[MAX_N];
int abc[D][D][D];
int firstocc[D][D][D];
int ab[D][D], bc[D][D], ac[D][D];
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int p; cin >> p;
    rep(i, 0, p){
        cin >> a[i];
    }
    memset(firstocc, -1, sizeof firstocc);
    const int req = (p + 40 - 1) / 40 + 1;
    vector<array<int, 6>> ans;
    rep(n, 1, p+1){
        rep(m, 1, p+1){
            rep(i, 0, p+1){
                if(i + n + m >= p){
                    break;
                }
                abc[a[i]][a[i + n]][a[i + n + m]]++;
                ab[a[i]][a[i + n]]++;
                ac[a[i]][a[i + n + m]]++;
                bc[a[i + n]][a[i + n + m]]++;
                if(firstocc[a[i]][a[i + n]][a[i + n + m]] == -1){
                    firstocc[a[i]][a[i + n]][a[i + n + m]] = i;
                }
            }

            rep(i, 0, D){
                rep(j, 0, D){
                    rep(k, 0, D){
                        if(abc[i][j][k] < req) continue;
                        if(abc[i][j][k] == ab[i][j] && ab[i][j] == ac[i][k] && ac[i][k] == bc[j][k]){
                            ans.push_back({firstocc[i][j][k], n, m, i, j, k});
                        }
                    }
                }
            }
            memset(abc, 0, sizeof abc);
            memset(ab, 0, sizeof ab);
            memset(ac, 0, sizeof ac);
            memset(bc, 0, sizeof bc);
            memset(firstocc, -1, sizeof firstocc);
        }
    }
    sort(all(ans));
    if(sz(ans) == 0){
        cout << "random sequence\n";
    }
    else{
        for(auto [start, n, m, i, j, k] : ans){
            cout << "triple correlation " << i << "(" << n << ")" << j << "(" << m << ")" << k << " found\n";
        }
    }
    
    return 0;
}
