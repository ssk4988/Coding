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

ll M = 1e9 + 7;
ll base = 29;
ll mod(ll v)
{
    return (v % M + M) % M;
}

ll modpow(ll b, ll pow)
{
    if (pow == 0)
        return 1;
    if (pow == 1)
        return b;
    ll res = modpow(b, pow / 2);
    res = mod(res * res);
    if (pow % 2)
    {
        res = mod(res * b);
    }
    return res;
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

vector<ll> bp;
vector<ll> pref;
vi ans;
vector<bool> good;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    string str;
    cin >> str;
    int n = str.length();
    bp.pb(1);
    pref.pb(str[0] - 'a' + 1);
    good.pb(false);
    rep(i, 1, n)
    {
        bp.pb(mod(bp[i - 1] * base));
        pref.pb(mod(pref[i - 1] + mod(bp[i] * (str[i] - 'a' + 1))));
        good.pb(false);
    }

    // good[n-1] = true;
    bp.pb(mod(bp[n - 1] * base));
    rep(i, 0, n)
    {
        if (good[i])
            continue;
        int len = i + 1;
        ll inv, y;
        gcdExtended(bp[len] - 1, M, &inv, &y);
        inv = (inv % M + M) % M;
        ll hash = mod(mod(pref[i] * (bp[n / len * len] - 1)) * inv);
        int rem = n % len;
        if (rem)
        {
            hash = mod(hash + mod(pref[rem - 1] * bp[n - rem]));
        }
        if (hash == pref[n - 1])
        {
            for (int j = len; j <= n; j += len)
            {
                good[j - 1] = true;
            }
            // break;
        }
    }
    rep(i, 0, n)
    {
        if (good[i])
            cout << i + 1 << " ";
    }
    cout << nL;

    return 0;
}