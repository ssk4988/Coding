#include <bits/stdc++.h>
using namespace std;

// #pragma GCC optimize ("Ofast")
// #pragma GCC target ("avx2")

using ll = long long;
using vi = vector<int>;
using pi = pair<int, int>;
using vpi = vector<pi>;
using ld = double;
using vld = vector<ld>;

#define sz(x) (int)x.size()
#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) begin(x), end(x)

// typedef complex<ld> C;
// typedef vector<ld> vd;
// void fft(vector<C> &a)
// {
//     int n = sz(a), L = 31 - __builtin_clz(n);
//     static vector<complex<long double>> R(2, 1);
//     static vector<C> rt(2, 1);
//     for (static int k = 2; k < n; k *= 2)
//     {
//         R.resize(n);
//         rt.resize(n);
//         auto x = polar(1.0L, acos(-1.0L) / k);
//         rep(i, k, 2 * k) rt[i] = R[i] = i & 1 ? R[i / 2] * x : R[i / 2];
//     }
//     vi rev(n);
//     rep(i, 0, n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
//     rep(i, 0, n) if (i < rev[i]) swap(a[i], a[rev[i]]);
//     for (int k = 1; k < n; k *= 2)
//     {
//         for (int i = 0; i < n; i += 2 * k)
//             rep(j, 0, k)
//             {
//                 C z = rt[j + k] * a[i + j + k];
//                 a[i + j + k] = a[i + j] - z;
//                 a[i + j] += z;
//             }
//     }
// }
// vd conv(const vd &a, const vd &b)
// {
//     if (a.empty() || b.empty())
//         return {};
//     vd res(sz(a) + sz(b) - 1);
//     int L = 32 - __builtin_clz(sz(res)), n = 1 << L;
//     vector<C> in(n), out(n);
//     copy(all(a), begin(in));
//     rep(i, 0, sz(b)) in[i].imag(b[i]);
//     fft(in);
//     for (C &x : in)
//         x *= x;
//     rep(i, 0, n) out[i] = in[-i & (n - 1)] - conj(in[i]);
//     fft(out);
//     rep(i, 0, sz(res)) res[i] = imag(out[i]) / (4 * n);
//     return res;
// }
ld dp[10005][55][2];
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc;
    cin >> nc;
    rep(cn, 0, nc)
    {
        int n;
        cin >> n;
        vi items(n);
        vld p(n);
        rep(i, 0, n) cin >> items[i] >> p[i];
        int a;
        cin >> a;
        // vd res(a + 1);
        // res[0] = 1;
        // vector<vector<vld>> prevdp;
        vld prevdp(a + 1);
        prevdp[0] = 1;
        // vector<vector<vld>> dp(a + 1, vector<vld>(55, vld(2)));
        rep(t, 0, n)
        {
            rep(i, 0, a + 1){
                rep(j, 0, items[t] + 1){
                    rep(k, 0, 2){
                        dp[i][j][k] = 0;
                    }
                }
            }
            rep(i, 0, a + 1){
                dp[i][0][1] = prevdp[i];
            }
            
            rep(i, 0, a)
            {
                rep(j, 0, items[t] + 1)
                {
                    rep(k, 0, 2)
                    {
                        if (k == 1)
                        {
                            dp[i][j][k] += dp[i][j][k - 1];
                            dp[i + 1][j][1] += dp[i][j][k] * (1 - p[t]);
                            if (j + 1 <= items[t])
                            {
                                dp[i + 1][j + 1][0] += dp[i][j][k] * p[t];
                            }
                        }
                    }
                }
            }
            // vd c(a + 1);
            // rep(i, 0, a + 1)
            // {
            //     c[i] = dp[i][items[t]][0];
            // }
            // res = conv(res, c);
            // if(sz(res) > a + 5) res.resize(a + 5);
            // prevdp = dp;
            rep(i, 0, a + 1){
                prevdp[i] = dp[i][items[t]][0];
            }
        }
        ld ans = 0;
        rep(i, 0, a + 1){
            ans += prevdp[i];
        }
        cout << fixed << setprecision(3) << ans << "\n";
    }
}
