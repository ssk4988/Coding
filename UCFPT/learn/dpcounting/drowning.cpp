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

const ll mod = 1000000007; // faster if const

ll modpow(ll b, ll e) {
	ll ans = 1;
	for (; e; b = b * b % mod, e /= 2)
		if (e & 1) ans = ans * b % mod;
	return ans;
}
vector<ll> berlekampMassey(vector<ll> s)
{
    int n = sz(s), L = 0, m = 0;
    vector<ll> C(n), B(n), T;
    C[0] = B[0] = 1;
    ll b = 1;
    rep(i, 0, n)
    {
        ++m;
        ll d = s[i] % mod;
        rep(j, 1, L + 1) d = (d + C[j] * s[i - j]) % mod;
        if (!d)
            continue;
        T = C;
        ll coef = d * modpow(b, mod - 2) % mod;
        rep(j, m, n) C[j] = (C[j] - coef * B[j - m]) % mod;
        if (2 * L > i)
            continue;
        L = i + 1 - L;
        B = T;
        b = d;
        m = 0;
    }
    C.resize(L + 1);
    C.erase(C.begin());
    for (ll &x : C)
        x = (mod - x) % mod;
    return C;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    const int N = 10;
    vector<vl> c(N, vl(N));
    rep(n, 1, N)
    {
        vi perm(n);
        iota(all(perm), 0);
        vi cnt(n + 1);
        do
        {
            int run = 1;
            int mxrun = 1;
            bool dir = true; // 1 inc, 0 dec
            rep(i, 1, n)
            {
                if (run == 1)
                {
                    run++;
                    dir = perm[i] > perm[i - 1];
                }
                else
                {
                    if (dir && perm[i] > perm[i - 1] || !dir && perm[i] < perm[i - 1])
                        run++;
                    else
                        run = 2, dir = !dir;
                }
                mxrun = max(run, mxrun);
            }
            cnt[mxrun]++;
        } while (next_permutation(all(perm)));
        vi pref(cnt);
        partial_sum(all(pref), pref.begin());
        rep(i, 1, n + 1)
        {
            c[n - i][n] = cnt[i];
            cout << n << " run of " << i << " cnt=" << cnt[i] << " pref=" << pref[i] << "\n";
        }
    }
    rep(i, 0, N){
        vl res = berlekampMassey(c[i]);
        cout << i << " " << sz(res) << ": ";
        for(ll x : res) cout << x << " ";
        cout << "\n";
    }

    return 0;
}
