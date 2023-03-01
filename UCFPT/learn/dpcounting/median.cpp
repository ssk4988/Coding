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
using vvi = vector<vl>;

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

vector<vvi> gendp(int n)
{
    vector<vvi> dp;
    int invbound = n * (n - 1) / 2;
    dp = vector<vvi>(n + 1, vvi(n + 1, vl(invbound + 1, 0)));
    dp[0][0][0] = 1;

    rep(i, 0, n)
    {
        rep(j, 0, i + 1)
        {
            int numb = i - j;
            rep(l, 0, invbound + 1)
            {
                if (dp[i][j][l] == 0)
                    continue;
                // add a
                // cout << i << " " << j << " " << l << nL;
                dp[i + 1][j + 1][l + numb] += dp[i][j][l];
                // add b
                dp[i + 1][j][l] += dp[i][j][l];
            }
        }
    }
    return dp;
}

void solve(int n, int k, vector<vvi> &dp)
{
    ll numtot = 0;
    rep(j, 0, n + 1)
    {
        numtot += dp[n][j][k];
    }

    auto findstr = [&](string &res, ll kth, int len, int numa, int numinv, auto &&findstr) -> void
    {
        assert(numinv >= 0);
        int lenleft = n - len;
        if (lenleft == 0)
            return;
        ll ways = 0;
        int numb = len - numa;
        // consider lenleft - 1
        lenleft--;
        rep(i, 0, lenleft + 1)
        {
            // i represents numa in leftover string
            int invleft = numinv - (numb * i) - numb; // sub out inv created by new string and added a
            if (invleft >= 0)
            {
                ways += dp[lenleft][i][invleft];
            }
        }
        if (ways >= kth)
        {
            res += "A";
            findstr(res, kth, len + 1, numa + 1, numinv - numb, findstr);
        }
        else
        {
            res += "B";
            findstr(res, kth - ways, len + 1, numa, numinv, findstr);
        }
    };
    vl qs;
    if (numtot % 2 == 0)
    {
        qs.pb(numtot / 2);
    }
    qs.pb(numtot / 2 + 1);
    // qs.pb(1);
    // qs.pb(2);
    // rep(i, 0, numtot){
    //     qs.pb(i + 1);
    // }
    // cout << numtot << nL;
    for (ll i : qs)
    {
        string ans = "";
        findstr(ans, i, 0, 0, k, findstr);
        int invcnt = 0, bcnt = 0;
        rep(j, 0, n)
        {
            if (ans[j] == 'B')
                bcnt++;
            else
                invcnt += bcnt;
        }
        assert(invcnt == k);
        cout << ans << nL;
    }
}

int main()
{
    // cin.tie(0)->sync_with_stdio(0);
    // cin.exceptions(cin.failbit);
    int n, k;
    cin >> n >> k;
    vector<vvi> dp = gendp(n);
    solve(n, k, dp);

    return 0;
}
