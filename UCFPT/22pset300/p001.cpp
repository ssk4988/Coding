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
vvi c;

ll nFormed = 0;
bool canForm(int index, ll budget)
{
    if (budget < 0)
        return false;
    if (index == n || (c[index].size() > 1 && c[index][1] > budget))
    {
        nFormed++;
        return nFormed >= k;
    }
    for (int v : c[index])
    {
        if (v > budget)
            break;
        if (canForm(index + 1, budget - v))
            return true;
    }

    return false;
}

ll savings = 0;
void calc(int index, ll budget)
{
    if (0 > budget)
        return;
    if (index == n || (c[index].size() > 1 && c[index][1] > budget))
    {
        savings += budget;
        return;
    }
    for (int v : c[index])
    {
        if (v > budget)
            break;
        calc(index + 1, budget - v);
    }
}

int main()
{
    // freopen("roboherd.in", "r", stdin);
    // freopen("roboherd.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> k;
    ll norm = 0;
    ll low = 0;
    ll high = 0;
    rep(i, 0, n)
    {
        int m;
        cin >> m;
        vi row(m);
        rep(j, 0, m)
        {
            cin >> row[j];
        }
        sort(all(row));
        norm += row[0];
        if (m == 1)
        {
            i--;
            n--;
            continue;
        }
        for (int j = m - 1; j >= 0; j--)
        {
            row[j] -= row[0];
        }
        high += row[m - 1];

        c.pb(row);
    }
    sort(all(c));
    while (low < high)
    {
        ll mid = low + (high - low) / 2;
        nFormed = 0;
        if (canForm(0, mid))
        {
            high = mid;
        }
        else
        {
            low = mid + 1;
        }
    }
    calc(0, low);
    ll ans = (low + norm) * k - savings;
    cout << ans << nL;

    return 0;
}