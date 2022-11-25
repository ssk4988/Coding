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

const int n = 7;
int dp[n + 1];

void genperm(vi &cur, vector<bool> &used)
{
    if (cur.size() == n)
    {
        vi cur2 = cur;
        int cnt = 0;
        rep(i, 0, n)
        {
            while (cur2[i] != i)
            {
                cnt++;
                swap(cur2[i], cur2[cur2[i]]);
            }
        }
        dp[cnt]++;
        return;
    }

    for (int i = 0; i < n; i++)
    {
        if (used[i])
            continue;
        used[i] = true;
        cur.pb(i);
        genperm(cur, used);
        cur.pop_back();
        used[i] = false;
    }
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    vi k;
    vector<bool> used(n, false);
    genperm(k, used);
    rep(i, 0, n + 1){
        cout << i << " " << dp[i] << nL;
    }
    return 0;
}