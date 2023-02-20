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

struct eq
{
    vector<pair<int, ld>> coef; //-1 for constant term in augmented matrix
    ld constant = 0;
    int minv = 0;
    map<int, ld> maps;
    void div(ld v)
    {
        constant /= v;
        for (auto &p : coef)
        {
            p.s /= v;
        }
    }
    eq scale(ld v)
    {
        eq res;
        res.constant = constant * v;
        for (auto &p : coef)
        {
            res.coef.pb({p.f, p.s * v});
        }
        return res;
    }
    eq operator-(eq other)
    {
        eq res;
        res.constant = constant - other.constant;
        int i1 = 0, i2 = 0;
        while (i1 < coef.size() || i2 < other.coef.size())
        {
            int nex = INT_MAX;
            ld newcoef = 0;
            if (i1 < coef.size())
            {
                nex = min(coef[i1].f, nex);
            }
            if (i2 < other.coef.size())
            {
                nex = min(other.coef[i2].f, nex);
            }
            if (i1 < coef.size() && coef[i1].f == nex)
            {
                newcoef += coef[i1].s;
                i1++;
            }
            if (i2 < other.coef.size() && other.coef[i2].f == nex)
            {
                newcoef -= other.coef[i2].s;
                i2++;
            }
            if (abs(newcoef) > eps)
            {
                res.coef.pb({nex, newcoef});
            }
        }
        return res;
    }
};

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
    vector<eq> eqs(h * w);
    vvi first(h * w);
    rep(i, 0, h)
    {
        rep(j, 0, w)
        {
            int c = encode(i, j);
            // eqs[c].coef.pb({c, 1});
            eqs[c].maps[c] = 1;
            if (grid[i][j] == 'X' || grid[i][j] == 'T')
            {
            }
            else
            {

                map<int, ld> t1;
                ld sumt = 0;
                rep(k, 0, 4)
                {
                    int i1 = i + ds[k][0], j1 = j + ds[k][1];
                    int res = 0;
                    if (i1 < 0 || j1 < 0 || i1 >= h || j1 >= w || grid[i1][j1] == 'X')
                    {
                        continue;
                    }
                    else
                    {
                        res = encode(i1, j1);
                    }
                    sumt += tp[k];
                    t1[res] += tp[k];
                }
                // for (auto &p : t1)
                // {
                //     eqs[p.f].coef.pb({c, -p.s / sumt});
                // }
                for (auto &p : t1)
                {
                    eqs[p.f].maps[c] -= p.s / sumt;
                }
                // trans[encode(i, j)] = t1;
                if (i == 0)
                {
                    eqs[c].constant += ((ld)1) / numopen;
                }
            }
            // sort(all(eqs[c].coef));
            // if (eqs[c].coef.size() > 0)
            // {
            //     first[eqs[c].coef[0].f].pb(c);
            // }
        }
    }
    rep(i, 0, h)
    {
        rep(j, 0, w)
        {
            int c = encode(i, j);
            eq &th = eqs[c];
            // sort(all(th.coef));
            // vector<pair<int, ld>> newcoef;
            // pair<int, ld> cur(-1, 0);
            // auto push = [&]() -> void
            // {
            //     if (cur.f != -1 && abs(cur.s) > eps)
            //     {
            //         newcoef.pb(cur);
            //         cur = {-1, 0};
            //     }
            // };
            // rep(k, 0, th.coef.size())
            // {
            //     if (cur.f == -1 || cur.f != th.coef[k].f)
            //     {
            //         push();
            //         cur.f = th.coef[k].f;
            //     }
            //     cur.s += th.coef[k].s;
            // }
            // push();
            // sort(all(newcoef));
            // th.coef = newcoef;
            for (auto &p : th.maps)
            {
                th.coef.pb(p);
            }
            th.minv = th.coef.size() == 0 ? 0 : th.coef[0].f;
            first[th.minv].pb(c);
        }
    }
    rep(i, 0, sz(first))
    {
        if (first[i].size() < 2)
            continue;
        int best = -1;
        rep(j, 0, sz(first[i]))
        {
            if (best == -1 || abs(eqs[best].minv) < abs(eqs[first[i][j]].minv))
            {
                best = first[i][j];
            }
        }
        if (best == -1)
            continue;
        eqs[best].div(eqs[best].coef[0].s);
        rep(j, 0, sz(first[i]))
        {
            if (best == first[i][j])
                continue;
            // eq sub = ;
            eqs[first[i][j]] = eqs[first[i][j]] - eqs[best].scale(eqs[first[i][j]].coef[0].s / eqs[best].coef[0].s);
            // if (eqs[first[i][j]].coef.size() == 0)
            //     return 0;
            eqs[first[i][j]].minv = eqs[first[i][j]].coef.size() == 0 ? 0 : eqs[first[i][j]].coef[0].f;
            first[eqs[first[i][j]].minv].pb(first[i][j]);
        }
        first[i].clear();
        first[i].pb(best);
    }
    vector<ld> vals(h * w, -1);
    for (int i = first.size() - 1; i >= 0; i--)
    {
        rep(j, 0, first[i].size())
        {
            eq &e = eqs[first[i][j]];
            ld cur = e.constant;
            for (auto &p : e.coef)
            {
                if (vals[p.f] != -1)
                {
                    cur -= p.s * vals[p.f];
                }
            }
            for (auto &p : e.coef)
            {
                if (vals[p.f] == -1)
                {
                    vals[p.f] = cur / p.s;
                }
            }
        }
    }
    rep(i, 0, vals.size())
    {
        int r = i / w;
        int c = i % w;
        if (grid[r][c] == 'T')
        {
            cout << fixed << setprecision(8) << vals[i] << nL;
        }
    }

    return 0;
}
