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
    map<int, ld> coef; //-1 for constant term in augmented matrix
    ld constant = 0;
    void div(ld v)
    {
        constant /= v;
        for (auto &p : coef)
        {
            p.s /= v;
        }
    }
    eq scale(ld v){
        eq res;
        res.constant = constant * v;
        for (auto &p : coef)
        {
            res.coef[p.f] = p.s * v;
        }
        return res;
    }
    eq operator-(eq other)
    {
        eq res;
        res.constant = constant - other.constant;
        set<int> comb;
        for (auto &p : coef)
        {
            comb.insert(p.f);
        }
        for (auto &p : other.coef)
        {
            comb.insert(p.f);
        }
        for (int i : comb)
        {
            bool thishas = coef.find(i) != coef.end();
            bool thathas = other.coef.find(i) != other.coef.end();
            if (thishas)
            {
                res.coef[i] += coef[i];
            }
            if (thathas)
            {
                res.coef[i] -= other.coef[i];
            }
            if (res.coef.find(i) != res.coef.end() && abs(res.coef[i]) < eps)
            {
                res.coef.erase(i);
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
            eqs[c].coef[c] = 1;
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
                for (auto &p : t1)
                {
                    eqs[p.f].coef[c] -= p.s / sumt;
                }
                // trans[encode(i, j)] = t1;
                if (i == 0)
                {
                    eqs[c].constant += ((ld)1) / numopen;
                }
            }
            // if (eqs[c].coef.size() > 0)
            // {
            //     first[(*(eqs[c].coef.begin())).f].pb(c);
            // }
        }
    }
    rep(i, 0, h)
    {
        rep(j, 0, w)
        {
            int c = encode(i, j);
            if (eqs[c].coef.size() > 0)
            {
                first[(*(eqs[c].coef.begin())).f].pb(c);
            }
        }
    }
    rep(i, 0, sz(first))
    {
        if (first[i].size() == 0)
            continue;
        int best = -1;
        rep(j, 0, sz(first[i]))
        {
            if (best == -1 || abs(eqs[best].coef[i]) < abs(eqs[first[i][j]].coef[i]))
            {
                best = first[i][j];
            }
        }
        if (best == -1)
            continue;
        eqs[best].div(eqs[best].coef[i]);
        rep(j, 0, sz(first[i]))
        {
            if (best == first[i][j])
                continue;
            // eq sub = ;
            eqs[first[i][j]] = eqs[first[i][j]] - eqs[best].scale(eqs[first[i][j]].coef[i] / eqs[best].coef[i]);
            first[(*(eqs[first[i][j]].coef.begin())).f].pb(first[i][j]);
        }
        first[i].clear();
        first[i].pb(best);
    }
    vector<ld> vals(h * w, -1);
    for(int i = first.size() - 1; i >= 0; i--){
        rep(j, 0, first[i].size()){
            eq &e = eqs[first[i][j]];
            ld cur = e.constant;
            for(auto &p : e.coef){
                if(vals[p.f] != -1){
                    cur -= p.s * vals[p.f];
                }
            }
            for(auto &p : e.coef){
                if(vals[p.f] == -1){
                    vals[p.f] = cur / p.s;
                }
            }
        }
    }
    rep(i, 0, vals.size()){
        int r = i / w;
        int c = i % w;
        if(grid[r][c] == 'T'){
            cout << fixed << setprecision(8) << vals[i] << nL;
        }
    }

    return 0;
}
