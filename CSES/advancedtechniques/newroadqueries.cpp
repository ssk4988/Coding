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

map<pi, vi> queries;
map<pi, int> ansq;
vvi appearances;
vi ans;
int n, m, q;

struct UF
{
    vi e;
    UF(int n) : e(n, -1) {}
    bool sameSet(int a, int b) { return find(a) == find(b); }
    int size(int x) { return -e[find(x)]; }
    int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
    bool join(int a, int b, int d)
    {
        a = find(a), b = find(b);
        if (a == b)
            return false;
        if (appearances[a].size() < appearances[b].size())
            swap(a, b);
        e[a] += e[b];
        e[b] = a;
        pi p = {a, b};
        if (p.f > p.s)
        {
            swap(p.f, p.s);
        }
        for (auto &v : queries[p])
        {
            ans[v] = d;
        }
        queries[p].clear();
        ansq[p] = d;
        for (int b1 : appearances[b])
        {
            if (b1 != a)
            {
                appearances[a].pb(b1);
                p = {b1, b};
                if (p.f > p.s)
                    swap(p.f, p.s);
                pi p1 = {b1, a};
                if (p1.f > p1.s)
                    swap(p1.f, p1.s);

                for (int k : queries[p])
                {
                    if (ansq.find(p1) == ansq.end())
                    {
                        queries[p1].pb(k);
                    }
                    else
                    {
                        ans[k] = d;
                    }
                }
                queries[p].clear();
            }
        }
        appearances[b].clear();
        return true;
    }
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cin >> n >> m >> q;
    appearances.resize(n);
    ans.resize(q, -1);
    UF dsu(n);
    vpi roads(m), qry(q);
    rep(i, 0, m)
    {
        cin >> roads[i].f >> roads[i].s;
        roads[i].f--;
        roads[i].s--;
    }
    // self-loops?
    rep(i, 0, q)
    {
        cin >> qry[i].f >> qry[i].s;
        qry[i].f--;
        qry[i].s--;
        if (qry[i].f > qry[i].s)
            swap(qry[i].f, qry[i].s);
        queries[qry[i]].pb(i);
        appearances[qry[i].f].pb(qry[i].s);
        appearances[qry[i].s].pb(qry[i].f);
    }
    rep(i, 0, m)
    {
        dsu.join(roads[i].f, roads[i].s, i + 1);
    }
    rep(i, 0, q)
    {
        cout << ans[i] << nL;
    }

    return 0;
}