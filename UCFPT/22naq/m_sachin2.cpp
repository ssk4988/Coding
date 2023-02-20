#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<ll> vl;

#define nl '\n'
#define rep(i, a, b) for (int i = a; i < b; i++)
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

int n, m, q;
vector<vector<pii>> appearances;
vector<pii> ans;
vector<pii> queries;
// vector<bool> inq;
queue<int> qu;

struct UF
{
    vi e;
    UF(int n) : e(n, -1) {}
    bool sameSet(int a, int b) { return find(a) == find(b); }
    int size(int x) { return -e[find(x)]; }
    int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
    // pii resgroup(int a, int b)
    // {
    //     a = find(a), b = find(b);
    //     if (e[a] > e[b])
    //         swap(a, b);
    //     return {a, b};
    // }
    int getNewGroup(int a, int b)
    {
        a = find(a), b = find(b);
        if(a == b) return a;
        if(e[a] > e[b]) return b;
        return a;
    }
    bool join(int a, int b, int t)
    {
        a = find(a), b = find(b);
        if (a == b)
            return false;
        if (e[a] > e[b])
            swap(a, b);
        e[a] += e[b];
        e[b] = a;
        // for (int i = 0; i < sz(appearances[b]); i++)
        // {
        //     pii &p = appearances[b][i];
        //     if (p.second == 0)
        //     {
        //         queries[p.first].first = a;
        //     }
        //     else
        //     {
        //         queries[p.first].second = a;
        //     }
        //     appearances[a].push_back(p);
        //     if (queries[p.first].first == queries[p.first].second && ans[p.first].first == -1 && !inq[p.first])
        //     {
        //         inq[p.first] = true;
        //         qu.push(p.first);
        //     }
        // }
        // assert(appearances[a].size() <= 2 * q);

        return true;
    }
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> m >> q;
    appearances.resize(n);
    // inq = vector<bool>(q, false);
    vector<pair<int, pii>> edges(m);
    for (int i = 0; i < m; i++)
    {
        int u, v, t;
        cin >> u >> v >> t;
        u--;
        v--;

        edges[i] = {t, {u, v}};
    }
    sort(all(edges));
    for (int i = 0; i < q; i++)
    {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        queries.push_back({u, v});
        appearances[u].push_back({v, i});
        appearances[v].push_back({u, i});
    }
    UF uf(n);

    auto clearqueue = [&](int t) -> void
    {
        while (!qu.empty())
        {
            int val = qu.front();
            qu.pop();
            if (ans[val].first != -1 )
                continue;
            ans[val] = {t, uf.size(queries[val].first)};
        }
    };
    int prevt = -1;
    ans = vector<pii>(q, {-1, -1});
    for (int i = 0; i < m; i++)
    {
        int t = edges[i].first;
        int u = edges[i].second.first;
        int v = edges[i].second.second;
        if(prevt != t) clearqueue(prevt);

        prevt = t;
        if (uf.find(u) == uf.find(v))
            continue;
        // pii groups = uf.resgroup(u, v);
        int g = uf.getNewGroup(u, v);
        int rg = g == uf.find(u) ? uf.find(v) : uf.find(u);
        for (auto &p : appearances[rg])
        {
            // int q1 = p.second > 0 ? queries[p.first].second : queries[p.first].first;
            // int other = p.second == 0 ? queries[p.first].second : queries[p.first].first;
            int prevg = uf.find(p.first);
            if (uf.find(rg) == uf.find(prevg) || uf.find(g) == prevg)
            {
                qu.push(p.second);
            }
            else
            {
                appearances[g].push_back({prevg, p.second});
            }
        }
        appearances[rg].clear();

        uf.join(u, v, t);
        // if (i + 1 >= m || edges[i + 1].first > t)
        // {
        //     clearqueue(t);
        // }
    }
    clearqueue(prevt);
    for (int i = 0; i < q; i++)
    {
        cout << ans[i].first << " " << ans[i].second << "\n";
    }

    return 0;
}
