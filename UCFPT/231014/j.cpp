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

using ded = tuple<int, ll, ll>;
using ed = tuple<int, int, ll, ll>;
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m;
    cin >> n >> m;
    vector<vector<ded>> adj(n);
    vector<ed> edges;
    rep(i, 0, m)
    {
        int a, b;
        ll t, r;
        cin >> a >> b >> t >> r;
        a--, b--;
        adj[a].push_back({b, t, r});
        adj[b].push_back({a, t, r});
        edges.push_back({a, b, t, r});
    }
    vl dist(n, LLONG_MAX);
    vi visited(n);
    dist[n - 1] = 0;
    priority_queue<pl, vpl, greater<pl>> pq;
    pq.push({0, n - 1});
    while (!pq.empty())
    {
        auto [d, cur] = pq.top();
        pq.pop();
        if (visited[cur])
            continue;
        visited[cur] = true;
        for (auto [nex, t, r] : adj[cur])
        {
            if (!visited[nex] && dist[nex] > dist[cur] + r)
            {
                dist[nex] = dist[cur] + r;
                pq.push({dist[nex], nex});
            }
        }
    }
    // rep(i, 0, n) cout << dist[i] << endl;
    // cout << "did dijkstra" << endl;
    vvi optimalnext(n);
    for (auto [a, b, t, r] : edges)
    {
        if (dist[a] > dist[b])
            swap(a, b);
        if (dist[a] + r == dist[b])
            optimalnext[b].pb(a);
    }
    int pt, pr;
    cin >> pt;
    vpi turtlepath(pt);
    vl turtletime, turtlesleep;
    // turtletime.pb(0);
    turtlesleep.pb(0);
    rep(i, 0, pt)
    {
        cin >> turtlepath[i].f >> turtlepath[i].s;
        turtlepath[i].f--;
        auto [a, b, t, r] = edges[turtlepath[i].f];
        turtletime.pb(t);
        turtlesleep.pb(t);
        turtletime.pb(0);
        if (i == pt - 1)
            continue;
        turtlesleep.pb(turtlepath[i].s);
    }
    // cout << "read input" << endl;
    vl turtlepref(turtlesleep);
    rep(i, 0, sz(turtlepref) - 1) turtlepref[i + 1] += turtlepref[i];
    for (int i = sz(turtletime) - 2; i >= 0; i--)
        turtletime[i] += turtletime[i + 1];
    // rep(i, 0, sz(turtlepref)) cout << "turtle at:" << turtlepref[i] << " " << turtletime[i] << endl;
    cin >> pr;
    vi rabbitpath(pr + 1);
    vl rabbittime(pr + 1);
    int curt = 0, prevnode = 0;
    rep(i, 0, pr)
    {
        int edgeindex;
        cin >> edgeindex;
        edgeindex--;
        auto [a, b, t, r] = edges[edgeindex];
        rabbitpath[i + 1] = a == prevnode ? b : a;
        prevnode = rabbitpath[i + 1];
        curt += r;
        rabbittime[i + 1] = curt;
    }
    // cout << "found rabbit times" << sz(rabbitpath) << endl;
    // rep(i, 0, sz(rabbitpath)) cout << "rabbit at: " << rabbitpath[i] << " " << rabbittime[i] << endl;
    vi ans;
    int idx = 0; // where is turtle on path
    rep(i, 0, sz(rabbitpath) - 1)
    {
        curt = rabbittime[i];
        // cout << "try " << i << " at time " << curt << " at node " << rabbitpath[i] << endl;
        if (curt >= turtlepref.back())
            continue;
        // cout << "under time" << endl;
        int nextnode = rabbitpath[i + 1];
        // not diverging
        if (sz(optimalnext[rabbitpath[i]]) < 1 || (sz(optimalnext[rabbitpath[i]]) == 1 && optimalnext[rabbitpath[i]][0] == nextnode))
            continue;
        // cout << "diverges" << endl;
        int rabbitArrive = curt + dist[rabbitpath[i]];
        // cout << "arrive faster at " << rabbitArrive << " than " << rabbittime.back() << endl;
        if (rabbitArrive >= rabbittime.back())
            continue; // not strictly faster
        while (idx + 1 < sz(turtlepref) && turtlepref[idx] <= curt)
            idx++;
        int turtleArrive = turtlepref[idx] + turtletime[idx];
        // cout << rabbitpath[i] << " " << rabbitArrive << " " << turtleArrive << endl;
        if (rabbitArrive <= turtleArrive)
        {
            ans.pb(rabbitpath[i]);
            // cout << "added ans " << rabbitpath[i] + 1 << endl;
        }
    }
    sort(all(ans));
    cout << sz(ans) << nL;
    for (int i : ans)
        cout << (i + 1) << " ";
    cout << nL;

    return 0;
}
