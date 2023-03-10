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

int h, w;
int encode(int row, int col)
{
    return row * w + col;
}

vvi ds = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
vector<ld> tp;

ld eps = 1e-10;

vector<map<int, ld>> combine(vector<map<int, ld>> &l, vector<map<int, ld>> &r)
{
    vector<map<int, ld>> res;
    rep(i, 0, sz(l))
    {
        map<int, ld> t;
        for (auto &p : l[i])
        {
            auto [nxt, prob] = p;
            for (auto &p1 : r[nxt])
            {
                t[p1.f] += p1.s * prob;
            }
        }
        vi er;
        for (auto &p : t)
        {
            if (p.s < eps)
            {
                er.pb(p.f);
                // cout << "reduce stuff" << nL;
            }
        }
        for (auto j : er)
        {
            t.erase(j);
        }
        res.pb(t);
    }
    return res;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cin >> w >> h;
    ld u, d, l, r;
    cin >> u >> d >> l >> r;
    u /= 100, d /= 100, l /= 100, r /= 100;
    tp = {d, r, u, l};
    // vertically flipped?
    eps *= h * w;
    vector<vector<char>> grid(h, vector<char>(w));
    int numopen = 0;
    rep(i, 0, h)
    {
        string str;
        cin >> str;
        rep(j, 0, w)
        {
            grid[i][j] = str[j];
            if (grid[i][j] == '.' && i == 0)
                numopen++;
        }
    }
    vector<map<int, ld>> trans(h * w);
    rep(i, 0, h)
    {
        rep(j, 0, w)
        {
            if (grid[i][j] == 'X')
                continue;
            map<int, ld> t1;
            rep(k, 0, 4)
            {
                int i1 = i + ds[k][0], j1 = j + ds[k][1];
                int res = 0;
                if (i1 < 0 || j1 < 0 || i1 >= h || j1 >= w || grid[i][j] == 'T' || grid[i1][j1] == 'X')
                {
                    res = encode(i, j);
                }
                else
                {
                    res = encode(i1, j1);
                }
                t1[res] += tp[k];
            }
            trans[encode(i, j)] = t1;
        }
    }
    vector<map<int, ld>> trans2 = trans;
    rep(i, 0, 40)
    {
        trans2 = combine(trans2, trans2);
    }
    vector<ld> starting;
    map<int, ld> ans;
        rep(j, 0, w)
        {
            if (grid[0][j] == '.')
            {
                for (auto &p : trans2[encode(0, j)])
                {
                    ans[p.f] += (((ld)1) / numopen) * p.s;
                }
            }
        }
    for (auto &p : ans)
    {
        cout << fixed << setprecision(8) << p.s << nL;
    }

    return 0;
}
