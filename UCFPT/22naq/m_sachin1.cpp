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
vector<bool> inq;
queue<int> qu;

struct UF
{
    vi e;
    vi siz;
    UF(int n) : e(n, -1), siz(n, 1)
    {
        for (int i = 0; i < n; i++)
        {
            e[i] = -sz(appearances[i]);
        }
    }
    bool sameSet(int a, int b) { return find(a) == find(b); }
    int size(int x) { return siz[find(x)]; }
    int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
    bool join(int a, int b, int t)
    {
        a = find(a), b = find(b);
        if (a == b)
            return false;
        if (e[a] > e[b])
            swap(a, b);
        e[a] += e[b];
        e[b] = a;
        siz[a] += siz[b];
        for (int i = 0; i < sz(appearances[b]); i++)
        {
            pii &p = appearances[b][i];
            if (p.second == 0)
            {
                queries[p.first].first = a;
            }
            else
            {
                queries[p.first].second = a;
            }
            appearances[a].push_back(p);
            if (queries[p.first].first == queries[p.first].second && ans[p.first].first == -1 && !inq[p.first])
            {
                inq[p.first] = true;
                qu.push(p.first);
            }
        }
        assert(appearances[a].size() <= 2 * q);

        return true;
    }
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> m >> q;
    appearances.resize(n);
    inq = vector<bool>(q, false);
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
        appearances[u].push_back({i, 0});
        appearances[v].push_back({i, 1});
    }
    UF uf(n);
    ans = vector<pii>(q, {-1, -1});
    auto clearq = [&](int t) -> void
    {
        while (!qu.empty())
        {
            int val = qu.front();
            qu.pop();
            inq[val] = false;
            if (ans[val].first != -1)
                continue;
            ans[val] = {t, uf.size(queries[val].first)};
        }
    };
    int prevt = -1;
    for (int i = 0; i < m; i++)
    {
        int t = edges[i].first;
        int u = edges[i].second.first;
        int v = edges[i].second.second;
        if(prevt != t) clearq(prevt);
        prevt = t;
        uf.join(u, v, t);
        
    }
    clearq(prevt);
    for (int i = 0; i < q; i++)
    {
        cout << ans[i].first << " " << ans[i].second << "\n";
    }

    return 0;
}
