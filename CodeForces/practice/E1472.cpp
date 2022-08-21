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

    int nc;
    cin >> nc;
    rep(cn, 0, nc)
    {
        int n;
        cin >> n;
        int low[n], high[n];
        vi cc;
        rep(i, 0, n)
        {
            cin >> low[i] >> high[i];
            if (low[i] > high[i])
            {
                int tmp = low[i];
                low[i] = high[i];
                high[i] = tmp;
            }
            cc.pb(low[i]);
            cc.pb(high[i]);
        }
        sort(cc.begin(), cc.end());
        cc.resize(unique(cc.begin(), cc.end()) - cc.begin());
        vector<tuple<int, int, int>> v;
        rep(i, 0, n)
        {
            low[i] = lb(all(cc), low[i]) - cc.begin();
            high[i] = lb(all(cc), high[i]) - cc.begin();
            v.pb({high[i], low[i], i});
        }
        sort(all(v));
        set<pi> set;
        int ans[n];
        int p = -1;
        vpi q;
        for (auto e : v)
        {
            if (get<0>(e) > p)
            {
                p = get<0>(e);
                for (pi p1 : q)
                {
                    set.insert(p1);
                }
                q.clear();
            }
            pi m = {get<1>(e), -5};
            auto k = set.lb(m);
            if (set.size())
            {
                if (k == set.begin())
                {
                    k = set.end();
                }
                else
                {
                    k--;
                }
            }
            m.set = get<2>(e);
            if (k == set.end())
            {
                ans[get<2>(e)] = -1;
            }
            else
            {
                ans[get<2>(e)] = (*k).set + 1;
            }

            q.pb(m);
        }
        rep(i, 0, n)
        {
            cout << ans[i] << " ";
        }
        cout << nL;
    }

    return 0;
}