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

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

const int MXC = 12;
const int N = 102;
int dp[N][N][MXC][MXC], prefl[N][N][MXC][MXC], prefr[N][N][MXC][MXC];
ll choose[N][N];
const int mod = 998244353;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    choose[0][0] = 1;
    rep(i, 0, N-1) {
        rep(j, 0, i+1) {
            (choose[i+1][j] += choose[i][j]) %= mod;
            (choose[i+1][j+1] += choose[i][j]) %= mod;
        }
    }
    rep(cn, 0, nc) {
        int n; cin >> n;
        vi s(n);
        rep(i, 0, n) {
            cin >> s[i];
        }
        rep(l, 0, n) {
            rep(r, l, n) {
                rep(al, 0, MXC) {
                    rep(ar, 0, MXC) {
                        dp[l][r][al][ar] = prefl[l][r][al][ar] = prefr[l][r][al][ar] = 0;
                    }
                }
            }
        }
        auto isok = [&](int i) { return s[i] <= 0; };
        dp[0][0][0][1] = isok(0);
        rep(l, 1, n) {
            dp[l][l][1][0] = isok(l);
        }
        rep(v, 0, MXC) {
            prefl[0][0][v][1] = isok(0);
            rep(l, 1, n) {
                prefr[l][l][1][v] = isok(l);
            }
        }
        rep(v, 1, MXC) {
            prefr[0][0][0][v] = isok(0);
            rep(l, 1, n) {
                prefl[l][l][v][0] = isok(l);
            }
        }
        for(int l = n-1; l >= 0; l--) {
        rep(r, l+1, n) {
                rep(al, 0, MXC) {
                    rep(ar, 0, MXC) {
                        ll ans = 0;
                        // ll &ans = dp[l][r][al][ar];
                        // if(l == 0 && r == 1 && al == 0 && ar == 1) {
                        //     cerr << "wtf" << endl;
                        // }
                        rep(m, l, r+1) {
                            // int onleft = m-l, onright = r-m;
                            int bl = al, br = ar;
                            if(l != 0 || r != n-1) {
                                int left = r == n-1 || (l > 0 && m-l <= r-m);
                                if(left) bl--;
                                else br--;
                            }
                            if(min(bl, br) < 0) continue;
                            ll cont = 0;
                            if(s[m] != -1) {
                                rep(cl, 0, min(MXC, s[m]+1)) {
                                    int cr = s[m] - cl;
                                    if(cr >= MXC) continue;
                                    ll left = m > l ? dp[l][m-1][bl][cl] : (bl == 0 && cl == 0);
                                    ll right = m < r ? dp[m+1][r][cr][br] : (br == 0 && cr == 0);
                                    (cont += choose[r-l][m-l] * left % mod * right) %= mod;
                                }
                            } else {
                                ll left = m > l ? prefr[l][m-1][bl][MXC-1] : (bl == 0);
                                ll right = m < r ? prefl[m+1][r][MXC-1][br] : (br == 0);
                                (cont += choose[r-l][m-l] * left % mod * right) %= mod;
                            }
                            // if(cont != 0) {
                                (ans += cont) %= mod;
                                // cerr << "l=" << l << " r=" << r << " al=" << al << " ar=" << ar << " m=" << m << " cont=" << cont << endl;

                            // }
                        }
                        dp[l][r][al][ar] = ans;
                        // if(ans != 0) 
                        // cerr << "l=" << l << " r=" << r << " al=" << al << " ar=" << ar << " dp=" << ans << endl;
                        prefl[l][r][al][ar] = prefr[l][r][al][ar] = dp[l][r][al][ar];
                        if(al) (prefl[l][r][al][ar] += prefl[l][r][al-1][ar]) %= mod;
                        if(ar) (prefr[l][r][al][ar] += prefr[l][r][al][ar-1]) %= mod;
                    }

                }
            }
        }
        cout << dp[0][n-1][0][0] << "\n";
    }
    
    return 0;
}
