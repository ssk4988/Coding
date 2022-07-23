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

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m;
    cin >> n >> m;
    pair<bool, int> jiro[n];
    int cnt[2] = {0}; // def, atk
    rep(i, 0, n)
    {
        pair<bool, int> card;
        string set;
        cin >> set;
        card.f = set == "ATK";
        cin >> card.s;
        jiro[i] = card;
        cnt[card.f ? 1 : 0]++;
    }
    int mxdmg = 0;
    int ciel[m];
    multiset<int> set;
    rep(i, 0, m)
    {
        cin >> ciel[i];
    }
    sort(ciel, ciel + m);
    sort(jiro, jiro + n);
    int num = min(cnt[1], m);
    int dmg;
    rep(j, 0, num)
    {
        set.clear();
        rep(i, 0, m)
        {
            set.insert(ciel[i]);
        }
        dmg = 0;
        for (int i = n - cnt[1]; i <= n - cnt[1] + j; i++)
        {
            int k = *prev(set.end());
            if (jiro[i].s > k)
                break;
            dmg += k - jiro[i].s;
            set.erase(set.find(k));
        }
        mxdmg = max(mxdmg, dmg);
    }

    if (m > n)
    {
        dmg = 0;
        set.clear();
        rep(i, 0, m)
        {
            set.insert(ciel[i]);
        }
        bool works = true;
        for (int i = cnt[0] - 1; i >= 0; i--)
        {
            auto it = set.upper_bound(jiro[i].s);
            if (it == set.end())
            {
                works = false;
                break;
            }
            else
            {
                set.erase(set.find(*it));
            }
        }
        for (int i = n - 1; i >= cnt[0]; i--)
        {
            int k = *set.rbegin();
            if (jiro[i].s > k)
            {
                works = false;
                break;
            }
            dmg += k - jiro[i].s;
            set.erase(set.find(k));
        }
        for (auto &i : set)
        {
            dmg += i;
        }
        set.clear();

        if (works)
            mxdmg = max(mxdmg, dmg);
    }
    cout << mxdmg << nL;

    return 0;
}