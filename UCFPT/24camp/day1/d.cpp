#pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pi = pair<int, int>;
using pl = pair<ll, ll>;
using pd = pair<ld, ld>;
using vi = vector<int>;
using vl = vector<ll>;
// using vd = vector<ld>;
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

typedef complex<double> C;
typedef vector<double> vd;
void fft(vector<C> &a)
{
    int n = sz(a), L = 31 - __builtin_clz(n);
    static vector<complex<long double>> R(2, 1);
    static vector<C> rt(2, 1); // (^ 10% faster if double)
    for (static int k = 2; k < n; k *= 2)
    {
        R.resize(n);
        rt.resize(n);
        auto x = polar(1.0L, acos(-1.0L) / k);
        rep(i, k, 2 * k) rt[i] = R[i] = i & 1 ? R[i / 2] * x : R[i / 2];
    }
    vi rev(n);
    rep(i, 0, n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
    rep(i, 0, n) if (i < rev[i]) swap(a[i], a[rev[i]]);
    for (int k = 1; k < n; k *= 2)
        for (int i = 0; i < n; i += 2 * k)
            rep(j, 0, k)
            {
                // C z = rt[j+k] * a[i+j+k]; // (25% faster if hand-rolled)  /// include-line
                auto x = (double *)&rt[j + k], y = (double *)&a[i + j + k]; /// exclude-line
                C z(x[0] * y[0] - x[1] * y[1], x[0] * y[1] + x[1] * y[0]);  /// exclude-line
                a[i + j + k] = a[i + j] - z;
                a[i + j] += z;
            }
}
vd conv(const vd &a, const vd &b)
{
    if (a.empty() || b.empty())
        return {};
    vd res(sz(a) + sz(b) - 1);
    int L = 32 - __builtin_clz(sz(res)), n = 1 << L;
    vector<C> in(n), out(n);
    copy(all(a), begin(in));
    rep(i, 0, sz(b)) in[i].imag(b[i]);
    fft(in);
    for (C &x : in)
        x *= x;
    rep(i, 0, n) out[i] = in[-i & (n - 1)] - conj(in[i]);
    fft(out);
    rep(i, 0, sz(res)) res[i] = imag(out[i]) / (4 * n);
    return res;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    string astr, bstr;
    cin >> astr >> bstr;
    int n = sz(astr), m = sz(bstr);
    vi a(n), b(m);
    rep(i, 0, n) a[i] = astr[i] == '1' ? 1 : -1;
    rep(i, 0, m) b[i] = bstr[i] == '1' ? 1 : -1;
    const int k = 3000;
    int nk = n / k;
    int q;
    cin >> q;
    vi ans(q);
    vector<vi> bucket(nk);
    vi p1(q), p2(q), len(q), target(q);
    rep(i, 0, q)
    {
        // int p1, p2, len;
        cin >> p1[i] >> p2[i] >> len[i];
        target[i] = p2[i] + len[i];
        while (p2[i] < target[i])
        {
            if (p1[i] % k == 0 && p2[i] + k <= target[i])
            {
                bucket[p1[i] / k].push_back(i);
                // ans[i] += block[p2][p1 / k];
                // p1 += k;
                // p2 += k;
                break;
            }
            else
            {
                ans[i] += a[p1[i]] != b[p2[i]];
                p1[i]++;
                p2[i]++;
            }
        }
    }
    vi block(m); // ith index in b, jth block in a
    vd bd(m);
    rep(i, 0, m) bd[i] = b[i];
    vd ad(k);
    vd res(sz(a) + sz(b) - 1);
    const int L = 32 - __builtin_clz(sz(res)), N = 1 << L;
    vector<C> in(N), out(N);
    rep(i, 0, nk)
    {
        rep(j, 0, k)
        {
            ad[j] = a[i * k + j];
        }
        reverse(all(ad));
        // vd res = conv(bd, ad);
        // int L = 32 - __builtin_clz(sz(res)), N = 1 << L;
        copy(all(a), begin(in));
        rep(i, 0, sz(b)) in[i].imag(b[i]);
        fft(in);
        for (C &x : in)
            x *= x;
        rep(i, 0, N) out[i] = in[-i & (N - 1)] - conj(in[i]);
        fft(out);
        rep(i, 0, sz(res)) res[i] = imag(out[i]) / (4 * N);
        // return res;
        rep(j, 0, m)
        {
            if (j + k > m)
                continue;
            // num 1*1 + num-1*-1 - num-1*1 - num1*-1 = res
            // num 1*1 + num-1*-1 + num-1*1 + num1*-1 = k
            // num-1*1 + num1*-1 = (k - res) / 2
            int val = round(res[j + k - 1]);
            block[j] = (k - val) / 2;
            // assert((k - val) % 2 == 0);
        }
        for (auto qidx : bucket[i])
        {
            ans[qidx] += block[p2[qidx]];
            p1[qidx] += k;
            p2[qidx] += k;
            if (p1[qidx] % k == 0 && p2[qidx] + k <= target[qidx])
                bucket[p1[qidx] / k].push_back(qidx);
        }
        bucket[i].clear();
    }
    rep(i, 0, q)
    {
        while (p2[i] < target[i])
        {
            if (p1[i] % k == 0 && p2[i] + k <= target[i])
            {
                assert(false);
            }
            else
            {
                ans[i] += a[p1[i]] != b[p2[i]];
                p1[i]++;
                p2[i]++;
            }
        }
        cout << ans[i] << "\n";
    }
    return 0;
}
