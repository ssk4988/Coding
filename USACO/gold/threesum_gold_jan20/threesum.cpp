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

#define maxN 5005

ll dp[maxN][maxN];
int a[maxN];
int n, q;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    freopen("threesum.in", "r", stdin);
    freopen("threesum.out", "w", stdout);
    cin >> n >> q;
    int msize = 0;
    unordered_map<int, int> comp;
    rep(i, 0, n)
    {
        cin >> a[i];
        if (comp.find(a[i]) == comp.end())
        {
            comp[a[i]] = msize++;
        }
    }
    for (int i = n - 1; i >= 0; i--)
    {
        int m[msize];
        memset(m, 0, sizeof m);
        for (int j = i + 2; j < n; j++)
        {
            m[comp[a[j - 1]]]++;
            int target = -(a[i] + a[j]);
            int cnt = 0;
            if (comp.find(target) != comp.end())
            {
                cnt = m[comp[target]];
            }

            dp[i][j] = dp[i + 1][j] + dp[i][j - 1] - dp[i + 1][j - 1] + cnt;
        }
    }
    rep(i, 0, q)
    {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        cout << dp[a][b] << nL;
    }

    return 0;
}