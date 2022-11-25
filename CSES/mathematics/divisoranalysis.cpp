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

ll m = 1000000007;
ll mod(ll k, ll m1)
{
    return (k % m1 + m1) % m1;
}
ll mod(ll k)
{
    return mod(k, m);
}

ll modpow(ll b, ll p, ll m1)
{
    if (p == 0)
        return 1;
    if (p == 1)
        return b;
    ll a = modpow(b, p / 2, m1);
    return mod(mod(a * a, m1) * modpow(b, p % 2, m1), m1);
}
ll modpow(ll b, ll p)
{
    return modpow(b, p, m);
}

ll gcdExtended(ll a, ll b, ll *x, ll *y)
{

    // Base Case
    if (a == 0)
    {
        *x = 0, *y = 1;
        return b;
    }

    // To store results of recursive call
    ll x1, y1;
    ll gcd = gcdExtended(b % a, a, &x1, &y1);

    // Update x and y using results of recursive
    // call
    *x = y1 - (b / a) * x1;
    *y = x1;

    return gcd;
}

ll modinv(ll A, ll M)
{
    ll x, y;
    ll g = gcdExtended(A, M, &x, &y);
    if (g != 1)
        return -1;
    else
    {
        return (x % M + M) % M;
    }
}

ll modinv(ll k)
{
    return modinv(k, m);
}
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n;
    cin >> n;
    vector<pair<ll, ll>> factors(n);
    ll numdivisors = 1, sumdivisors = 1, proddivisors = 1;
    ll sqrtprod = 1, prod = 1;
    bool isperfectsq = true;
    rep(i, 0, n)
    {
        cin >> factors[i].f >> factors[i].s;
        numdivisors = mod(numdivisors * (factors[i].s + 1));
        proddivisors = mod(proddivisors * (factors[i].s + 1), m - 1);
        sumdivisors = mod(sumdivisors * mod(mod(modpow(factors[i].f, factors[i].s + 1) - 1) * modinv(factors[i].f - 1)));
        sqrtprod = mod(sqrtprod * modpow(factors[i].f, factors[i].s / 2));
        prod = mod(prod * modpow(factors[i].f, factors[i].s));
        isperfectsq &= factors[i].s % 2 == 0;
    }
    cout << modinv(2, m - 1) << nL;
    proddivisors = mod(proddivisors * modinv(2, m - 1), m - 1);
    proddivisors = modpow(prod, proddivisors);
    if (isperfectsq)
        proddivisors = mod(proddivisors * sqrtprod);
    cout << numdivisors << " " << sumdivisors << " " << proddivisors << nL;

    return 0;
}