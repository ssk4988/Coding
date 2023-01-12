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

int n, m;
int grid[400][400];
int hpref[2][400][400];

int query(int type, int row, int c1, int c2)
{
    int ans = hpref[type][row][c2];
    if (c1 > 0)
    {
        ans -= hpref[type][row][c1 - 1];
    }
    return ans;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        string str;
        cin >> str;
        for (int j = 0; j < m; j++)
        {
            if (str[j] == '.')
            {
                grid[i][j] = 0;
            }
            else if (str[j] == '#')
            {
                grid[i][j] = -1;
            }
            else
            {
                grid[i][j] = 1;
            }
            if (grid[i][j] == -1)
            {
                hpref[0][i][j]++;
            }
            if (grid[i][j] == 1)
            {
                hpref[1][i][j]++;
            }
            if (j > 0)
            {
                for (int k = 0; k < 2; k++)
                {
                    hpref[k][i][j] += hpref[k][i][j - 1];
                }
            }
        }
    }
    int ans = 0;
    for (int c1 = 0; c1 < m; c1++)
    {
    cols:
        for (int c2 = c1 + 2; c2 < m; c2++)
        {
            vvi medcnt(2);
            for (int i = 0; i < n; i++)
            {
                int k = query(1, i, c1 + 1, c2 - 1);
                int k1 = query(0, i, c1 + 1, c2 - 1);
                if (k1 > 0)
                    continue;
                rep(l, k, 2)
                {
                    medcnt[l].pb(i);
                }
            }
            // first sweep with no meds in cols
            int r1 = 0, r2 = 0;
            int num[] = {query(0, r1, c1, c1) + query(0, r1, c2, c2),
                         query(1, r1, c1, c1) + query(1, r1, c2, c2)};
            int point[] = {0, -1};
            while (r1 < n && r2 < n && medcnt[1].size() > 0)
            {
                while (r2 < n && (num[0] > 0 || num[1] > 0))
                {
                    for (int i = 0; i < 2; i++)
                    {
                        num[i] -= query(i, r1, c1, c1) + query(i, r1, c2, c2);
                    }
                    r1++;
                    if (r1 > r2)
                    {
                        r2++;
                        if (r2 >= n)
                            break;
                        for (int i = 0; i < 2; i++)
                        {
                            num[i] += query(i, r2, c1, c1) + query(i, r2, c2, c2);
                        }
                    }
                }
                while (r2 < n && num[0] == 0 && num[1] == 0)
                {
                    while (point[0] < medcnt[1].size() && medcnt[1][point[0]] < r1 + 1) // first element geq r1+1
                    {
                        point[0]++;
                    }
                    while (point[1] + 1 < medcnt[1].size() && medcnt[1][point[1] + 1] <= r2 - 1) //last element leq r2 - 1
                    {
                        point[1]++;
                    }
                    if (point[0] <= point[1])
                    {
                        ans = max(ans, c2 - c1 - 1 + (r2 - r1 + 1) * 2);
                    }
                    r2++;
                    if (r2 < n)
                    {
                        for (int i = 0; i < 2; i++)
                        {
                            num[i] += query(i, r2, c1, c1) + query(i, r2, c2, c2);
                        }
                    }
                }
            }
            // 2nd sweep
            r1 = 0;
            r2 = 0;
            num[0] = query(0, r1, c1, c1) + query(0, r1, c2, c2);
            num[1] = query(1, r1, c1, c1) + query(1, r1, c2, c2);
            point[0] = 0;
            point[1] = -1;
            while (r1 < n && r2 < n && medcnt[0].size() > 0)
            {
                while (r2 < n && (num[0] > 0 || num[1] > 1))
                {
                    for (int i = 0; i < 2; i++)
                    {
                        num[i] -= query(i, r1, c1, c1) + query(i, r1, c2, c2);
                    }
                    r1++;
                    if (r1 > r2)
                    {
                        r2++;
                        if (r2 >= n)
                            break;
                        for (int i = 0; i < 2; i++)
                        {
                            num[i] += query(i, r2, c1, c1) + query(i, r2, c2, c2);
                        }
                    }
                }
                while (r2 < n && num[0] == 0 && num[1] <= 1)
                {
                    while (point[0] < medcnt[0].size() && medcnt[0][point[0]] < r1 + 1)
                    {
                        point[0]++;
                    }
                    while (point[1] + 1 < medcnt[0].size() && medcnt[0][point[1] + 1] <= r2 - 1)
                    {
                        point[1]++;
                    }
                    if (point[0] <= point[1])
                    {
                        ans = max(ans, c2 - c1 - 1 + (r2 - r1 + 1) * 2);
                    }
                    r2++;
                    if (r2 < n)
                    {
                        for (int i = 0; i < 2; i++)
                        {
                            num[i] += query(i, r2, c1, c1) + query(i, r2, c2, c2);
                        }
                    }
                }
            }
        }
    }
    cout << ans << nL;

    return 0;
}