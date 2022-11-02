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

ll M = 1e9 + 7;
ll b = 29;
ll base[maxN];
ll pref[maxN];
ll rpref[maxN];
int dp[maxN][maxN];
ll cnt[maxN];
int n;

ll mod(ll k)
{
    return (k % M + M) % M;
}
ll hashrange(int l, int r)
{
    ll h = pref[r];
    if (l)
    {
        h = mod(h - pref[l - 1]);
    }
    h = mod(h * base[n - l]);
    return h;
}
ll rhashrange(int l, int r)
{
    ll h = rpref[r];
    if (l)
    {
        h = mod(h - mod(base[r - (l - 1)] * rpref[l - 1]));
    }
    h = mod(h * base[n]);
    return h;
}
ll hashpair(pi p)
{
    return hashrange(p.f, p.s);
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    string str;
    cin >> str;
    n = str.size();
    base[0] = 1;
    rpref[0] = pref[0] = (str[0] - 'a' + 1);
    rep(i, 1, n)
    {
        int k = str[i] - 'a' + 1;
        base[i] = mod(base[i - 1] * b);
        pref[i] = mod(pref[i - 1] + mod(k * base[i]));
        rpref[i] = mod(mod(rpref[i - 1] * b) + k);
    }
    rep(i, n, maxN)
    {
        base[i] = mod(base[i - 1] * b);
    }
    
    rep(i, 0, n)
    {
        dp[i][i] = 1;
        cnt[1]++;
        rep(j, i + 1, n)
        {
            int t = (j - i + 1) / 2;
            if (hashrange(i, i + t - 1) == rhashrange(j - t + 1, j) && hashrange(i, i + t - 1) != hashrange(j - t + 1, j))
            {
                dp[i][j] = 1;
                cnt[1]++;
                // cout << i << " " << j << " " << hashrange(i, i + t - 1) << " " << rhashrange(j - t + 1, j) << nL;
            }
        }
    }
    int j, t, l1, l2, r1, r2;
    rep(len, 2, n + 1)
    {
        rep(i, 0, n + 1 - len)
        {
            j = i + len - 1;
            t = len / 2;
            l1 = i, l2 = j - t + 1, r1 = i + t - 1, r2 = j;
            if(dp[i][j] != 0) continue;
            // cout << l1 << " " << r1 << " " << l2 << " " << r2 << nL;
            if (dp[l1][r1] == dp[l2][r2] && hashrange(l1, r1) == hashrange(l2, r2))
            {
                dp[i][j] = 1 + dp[l1][r1];
            }
            cnt[dp[i][j]]++;
        }
    }
    
    for(int i = n; i; i--){
        cnt[i - 1] += cnt[i];
    }
    rep(i, 1, n + 1)
    {
        cout << cnt[i] << " ";
    }
    cout << nL;

    return 0;
}