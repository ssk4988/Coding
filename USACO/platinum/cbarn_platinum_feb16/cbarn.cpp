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

int n, k;
vl freq, suff, suff1;
vector<vl> dp;

ll C(int i, int j, int k1)
{
    ll ans = suff1[i] - suff1[j + 1] - (n - j) * (suff[i] - suff[j + 1]);
    if (k1 == k && j + 1 < n)
    {
        ans += suff1[j + 1];
    }
    return ans;
}

void compute(int l, int r, int optl, int optr, int k1)
{
    if (l > r)
        return;
    int mid = (l + r) / 2;

    pair<ll, int> best = {LLONG_MAX, -1};
    for (int k = optl; k <= min(optr, mid); k++)
    {
        best = min(best, {(k ? dp[k1 - 1][k - 1] : 0) + C(k, mid, k1), k});
    }
    dp[k1][mid] = best.f;
    int opt = best.s;
    compute(l, mid - 1, optl, opt, k1);
    compute(mid + 1, r, opt, optr, k1);
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    freopen("cbarn.in", "r", stdin);
    freopen("cbarn.out", "w", stdout);
    cin >> n >> k;
    freq.resize(n);
    suff.resize(n);
    suff1.resize(n);
    ll ans = LLONG_MAX;
    rep(i, 0, n)
    {
        cin >> freq[i];
    }
    reverse(all(freq));
    vl freq1(freq);

    rep(shift, 0, n)
    {
        rep(i, 0, n)
        {
            freq[(i + shift) % n] = freq1[i];
        }
        for (int i = n - 1; i >= 0; i--)
        {
            suff[i] = freq[i];
            suff1[i] = freq[i] * (n - i);
            if (i + 1 < n)
            {
                suff[i] += suff[i + 1];
                suff1[i] += suff1[i + 1];
            }
        }
        dp = vector<vl>(k + 1, vl(n));
        // check k=1
        dp[1][0] = 0;
        if (k >= 2)
        {
            rep(i, 1, n)
            {
                dp[2][i] = C(1, i, 2);
            }
        }
        rep(k1, 3, k + 1)
        {
            compute(1, n - 1, 1, n - 1, k1);
        }

        if (k == 1)
            ans = min(ans, suff1[0] - suff[0]);
        else
        {
            rep(i, 1, n)
            {
                ans = min(ans, dp[k][i]);
            }
        }
    }

    cout << ans << nL;
    return 0;
}
