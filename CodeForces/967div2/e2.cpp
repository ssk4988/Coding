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
using vll = vector<pll>;;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    int MOD;
    rep(cn, 0, nc){
        int n, k; cin >> n >> k >> MOD;
        vector<vl> heap1(n+1, vl(k+1)), heap0(n+1, vl(k+1)), heap2(n+1, vl(k+1));
        vector lower(n+1, vector(k+1, vl(k+1))), higher(n+1, vector(k+1, vl(k+1)));
        // heap2[0] = vl(k+1, 1); // <- doesn't make sense
        heap1[0] = vl(k+1, 1);
        heap0[0] = vl(k+1, 1);
        rep(j, 0, k+1) {
            rep(l, 0, k+1) {
                lower[0][j][l] = j < l;
                higher[0][j][l] = j > l;
            }
        }
        rep(i, 1, n+1){
            vl heap1conv(k+1), heap0conv(k+1), lowconv(k+1), highconv(k+1);
            rep(j, 0, k+1){
                rep(l, 0, k+1){
                    if(j + l > k) break;
                    if(j > l) {
                        (heap1conv[j + l] += heap1[i-1][j] * heap0[i-1][l]) %= MOD;
                        if(j+1 <= k) (lower[i][j + l][j+1] += heap1[i-1][j] * heap0[i-1][l]) %= MOD;
                        if(j > 0) (higher[i][j + l][j-1] += heap1[i-1][j] * heap0[i-1][l]) %= MOD;
                    }
                    (heap0conv[j + l] += heap0[i-1][j] * heap0[i-1][l]) %= MOD;
                }
            }
            rep(j, 0, k+1){
                rep(l, 1, k+1){
                    (lower[i][j][l] += lower[i][j][l-1]) %= MOD;
                }
                for(int l = k-1; l >= 0; l--) {
                    (higher[i][j][l] += higher[i][j][l+1]) %= MOD;
                }
            }
            rep(j, 0, k+1){
                rep(l, 0, k+1){
                    if(j + l > k) break;
                    if(j > l) {
                        (lowconv[j + l] += lower[i-1][j][l] * heap1[i-1][l]) %= MOD;
                        (highconv[j + l] += higher[i-1][j][l] * heap0[i-1][l]) %= MOD;
                    }
                }
            }
            rep(j, 0, k+1){
                rep(p, 0, j+1) {
                    (heap1[i][j] += 2 * heap1conv[j - p]) %= MOD;
                    (heap0[i][j] += heap0conv[j - p]) %= MOD;
                    (heap2[i][j] += 2 * (lowconv[j - p] + highconv[j - p])) %= MOD;
                }
            }
        }
        cout << heap2[n-1][k] << "\n";
    }
    
    return 0;
}
