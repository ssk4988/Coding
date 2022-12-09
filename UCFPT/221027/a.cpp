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
#define maxN 20
int n;
ll dp[maxN + 1];
ll fact[maxN + 1];

vector<ll> dp1;

ll permute(int n, int k)
{
    return fact[n] / fact[n - k];
}

void genperm1(vi &cur, int left, ll k)
{
    if (left == 0)
    {
        dp1[n - cur.size()] += k;
        return;
    }
    for (int i = 1; i <= left; i++)
    {
        cur.pb(i);
        genperm1(cur, left - i, k * permute(left - 1, i - 1));
        cur.pop_back();
    }
}

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
    int a, b;
    cin >> n >> a >> b;
    vi k;
    dp1 = vector<ll>(n + 1);
    fact[0] = 1;
    rep(i, 1, n + 1)
    {
        fact[i] = fact[i - 1] * i;
    }
    genperm1(k, n, 1);
    // rep(i, 0, n + 1){
    //     cout << i << " " << dp1[i] << nL;
    // }
    ll pref[n + 1];
    pref[0] = dp1[0];
    rep(i, 1, n + 1)
    {
        pref[i] = pref[i - 1] + dp[i];
    }
    ld avg = 0;
    rep(i, 0, n + 1)
    {
        avg += (ld)i * dp1[i] / fact[n];
    }
    cout << avg << nL;
    vi current(n);
    rep(i, 0, n)
    {
        int c;
        cin >> c;
        c--;
        current[i] = c;
    }
    int curswaps = 0;
    vi cur2 = current;
    rep(i, 0, n)
    {
        while (cur2[i] != i)
        {
            curswaps++;
            swap(cur2[i], cur2[cur2[i]]);
        }
    }
    cout << "Current cost: " << (curswaps * a) << nL;
    cout << "Avg expected: " << (avg * a + b) << nL;
    avg = avg * a + b;
    ld oldcost = avg + 1;
    ld cost = 0;
    while(oldcost > avg){
        oldcost = avg;
        avg = 0;
        rep(i, 0, n + 1){
            avg += ((ld)dp1[i] / fact[n]) * min(oldcost + cost, (ld)a * i);
        }
        cost += b;
    }
    cout << "Avg converged: " << avg << nL;
    return 0;
}