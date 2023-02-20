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
    map<int, char> mf;
    mf[0] = 'w';
    mf[1] = 'i';
    mf[2] = 'n';
    rep(cn, 0, nc)
    {
        int n;
        cin >> n;
        vvi a(n, vi(3));
        vvi other = {{1, 2}};
        vvi exchange;
        vector<vector<deque<int>>> gn(3, vector<deque<int>>(3));
        // 0 dim: which give
        // 1 dim: which need

        rep(i, 0, n)
        {
            string str;
            cin >> str;
            rep(j, 0, 3)
            {
                if (str[j] == 'w')
                    a[i][0]++;
                if (str[j] == 'i')
                    a[i][1]++;
                if (str[j] == 'n')
                    a[i][2]++;
            }
            vi abundant;
            vi scarce;
            rep(j, 0, 3)
            {
                if (a[i][j] > 1)
                {
                    abundant.pb(j);
                }
                if (a[i][j] < 1)
                    scarce.pb(j);
            }
            for (int j : scarce)
            {
                gn[abundant[0]][j].push_back(i);
            }
        }


        // exchange 1
        rep(i, 0, 3)
        {
            rep(j, 0, 3)
            {
                if (i >= j)
                    continue;
                int times = min(gn[i][j].size(), gn[j][i].size());
                rep(k, 0, times)
                {
                    int v1 = gn[i][j].front();
                    int v2 = gn[j][i].front();
                    exchange.pb({v1, i, v2, j});
                    gn[i][j].pop_front();
                    gn[j][i].pop_front();
                }
            }
        }


        // exchange 2
        vvi perm = {{0, 1, 2}, {0, 2, 1}, {1, 0, 2}, {1, 2, 0}, {2, 0, 1}, {2, 1, 0}};
        rep(i, 0, perm.size())
        {
            int times = INT_MAX;
            rep(j, 0, 3)
            {
                int nex = j == 2 ? 0 : j + 1;
                times = min(times, sz(gn[perm[i][j]][perm[i][nex]]));
            }
            if (times == INT_MAX)
                continue;
            rep(j, 0, times)
            {
                rep(k, 0, 2)
                {
                    int nex = k == 2 ? 0 : k + 1;
                    int p1 = perm[i][k], p2 = perm[i][nex], p3 = perm[i][3 - k - nex];
                    int v1 = gn[p1][p2].front(); // gn[p1][p2].pop_front();
                    int v2 = gn[p2][p3].front(); // gn[p2][p3].pop_front();
                    exchange.pb({v1, perm[i][0], v2, p2});
                }
                rep(k, 0, 3)
                {
                    int nex = k == 2 ? 0 : k + 1;
                    gn[perm[i][k]][perm[i][nex]].pop_front();
                }
            }
        }
        cout << exchange.size() << nL;
        for (auto &v : exchange)
        {
            cout << (v[0] + 1) << " " << mf[v[1]] << " " << (v[2] + 1) << " " << mf[v[3]] << nL;
        }
    }

    return 0;
}
