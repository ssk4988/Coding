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

struct Chooses {
    const ll MOD;
    const int LIM;
    vl inv, fact, invfact;
    Chooses(int n, ll m) : LIM(n+1), MOD(m), inv(LIM), fact(LIM), invfact(LIM) {
        fact[0] = invfact[0] = inv[1] = fact[1] = invfact[1] = 1;
        rep(i, 2, LIM) {
            inv[i] = MOD - (MOD / i) * inv[MOD % i] % MOD;
            fact[i] = (i * fact[i - 1]) % MOD;
            invfact[i] = (inv[i] * invfact[i - 1]) % MOD;
        }
    }
    ll choose(int n, int k) {
        if (k > n || k < 0) return 0;
        return (fact[n] * invfact[k]) % MOD * invfact[n - k] % MOD;
    }
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n;
    cin >> n;
    Chooses c(1e6, 1e9+7);
    rep(i, 0, n)
    {
        int a, b;
        cin >> a >> b;
        cout << c.choose(a, b) << nL;
    }

    return 0;
}
