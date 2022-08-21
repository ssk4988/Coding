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

bool test(vi v, double val)
{
    double a[v.size() - 2];
    double sum = v[0] + v[v.size() - 1] - 2 * val;
    double best = -1000000009;
    double cur = 0;
    rep(i, 1, v.size() - 1)
    {
        a[i - 1] = v[i] - val;
        sum += a[i - 1];
        cur = a[i - 1] + max(0.0, cur);
        best = max(best, cur);
    }
    return sum - best >= 0;
}

int main()
{
    freopen("sabotage.in", "r", stdin);
    freopen("sabotage.out", "w", stdout);
    int n;
    cin >> n;
    vi v(n);
    rep(i, 0, n)
    {
        cin >> v[i];
    }
    double low = 0;
    double high = 10000;
    while (low + 0.0001 < high)
    {
        double mid = (low + high) / 2;
        if (!test(v, mid))
        {
            high = mid;
        }
        else
        {
            low = mid;
        }
    }
    printf("%.3f\n", low);

    return 0;
}