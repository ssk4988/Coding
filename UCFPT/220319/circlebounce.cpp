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
using vvl = vector<vl>;

#define f first
#define s second
#define mp make_pair
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

ll mod = 1000000007;
ll modulo(ll l){
    return (l % mod + mod) % mod;
}
ll gcd(ll a, ll b, ll *x, ll *y)
{
    if (b == 0)
    {
        *x = 1;
        *y = 0;
        return a;
    }
    ll x1 = 1, y1 = 1;
    ll gcd1 = gcd(b, a % b, &x1, &y1);

    *x = y1;
    *y = x1 - (a / b) * y1;
    return gcd1;
}

vvl matmul(vvl a, vvl b)
{
    vvl res;
    for (int i = 0; i < a.size(); i++)
    {
        vl row(b[0].size());
        for (int j = 0; j < b[0].size(); j++)
        {
            for (int k = 0; k < b.size(); k++)
            {
                row[j] = modulo(row[j] + modulo(a[i][k] * b[k][j]));
            }
        }
        res.pb(row);
    }
    return res;
}
vvl pow(vvl m, ll n)
{
    if (n == 1)
        return m;
    vvl m2 = pow(m, n / 2);
    m2 = matmul(m2, m2);
    if (n % 2 == 1)
    {
        m2 = matmul(m, m2);
    }
    return m2;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    ll a, b, n;
    cin >> a >> b >> n;
    n++;
    ll c = modulo(a * a + b * b);
    ll invc = 1, y = 1;
    ll gcd1 = gcd(c, mod, &invc, &y);
    vvl matrix;
    vl r1;
    r1.pb(modulo(a * a - b * b));
    r1.pb(modulo(2 * a * b));
    vl r2;
    r2.pb(modulo(-2 * a * b));
    r2.pb(modulo(a * a - b * b));
    matrix.pb(r1);
    matrix.pb(r2);
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            matrix[i][j] = modulo(matrix[i][j] * invc);
        }
    }
    vvl res = n == 0 ? matrix : pow(matrix, n);
    ll ans = modulo(-res[0][0]);
    cout << ans << "\n";
    return 0;
}