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

int n = 8;

vector<ld> prob(1 << 25, -1);

int encode(vi &p)
{
    int val = 0;
    for (int i = n - 1; i >= 0; i--)
    {
        val <<= 3;
        val += p[i];
    }
    return val;
}

vi decode(int val)
{
    vi res;
    rep(i, 0, n)
    {
        res.pb(val & 7);
        val >>= 3;
    }
    return res;
}

ld solve(int cur)
{
    if (prob[cur] >= 0)
        return prob[cur];

    prob[cur] = 0;
    int ways = 0;
    vi perm = decode(cur);
    rep(i, 0, n)
    {
        rep(j, i + 1, n)
        {
            if (perm[i] > perm[j])
            {
                ways++;
                swap(perm[i], perm[j]);
                int nv = encode(perm);
                swap(perm[i], perm[j]);
                prob[cur] += solve(nv);
            }
        }
    }
    if (ways == 0)
    {
        prob[cur] = 0;
    }
    else
    {
        prob[cur] /= ways;
        prob[cur]++;
    }

    return prob[cur];
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc;
    cin >> nc;
    rep(cn, 0, nc)
    {
        int k;
        cin >> k;
        vi start(8);
        rep(i, n - k, n)
        {
            cin >> start[i];
            start[i]--;
        }
        cout << fixed << setprecision(4) << solve(encode(start)) << nL;
    }

    return 0;
}
