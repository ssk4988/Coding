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

int n;
vi par;
vi subsz;
vvi child;
vi childcount;
ll timer = 0;
vector<int> sol;

bool cmp(int a, int b)
{
    return subsz[a] <= subsz[b];
}
priority_queue<pi> pq;

void solve(int k)
{
    vi path;
    path.pb(k); // create ascending heavy path from leaf to node
    while (child[path.back()].size())
    {
        int cur = path.back();
        path.pb(child[cur].back());// add heaviest child to path
        child[cur].pop_back();
    }
    for (int i = path.size() - 1; i > 0; i--)
    {
        for(int c : child[path[i]]) // push newly split subtrees into pq (at very bottom nothing should happen cuz no children)
        {
            pq.push({subsz[c], c});
        }
        sol[path[i]] = timer + subsz[path[i]]; // store time at which solved, though we dont need these
        subsz[path[i]] = 1 + (i + 1 < path.size() ? subsz[path[i + 1]] : 0); // update subsize to only include heavy path
        child[path[i]].clear();
    }
    int rootsubsz = 1 + (0 + 1 < path.size() ? subsz[path[0 + 1]] : 0);
    timer += subsz[k]; // we activated all nodes in subtree of pointer
    sol[k] = timer; // update root time
    path.clear();
    path.pb(k); // create a descending path
    while (child[path.back()].size())
    {
        int cur = path.back();
        path.pb(child[cur].back());
        child[cur].pop_back();
    }
    rep(i, 1, path.size())
    {
        timer += subsz[path[i - 1]] - subsz[path[i]];
        sol[path[i]] = timer;
    }
    subsz[k] = rootsubsz;
    timer += subsz[path.back()];
    rep(i, 0, path.size())
    {
        for (int c : child[path[i]])
        {
            pq.push({subsz[c], c});
        }
        child[path[i]].clear();
    }
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cin >> n;
    par = vi(n, -1);
    subsz = vi(n, 1);
    childcount = vi(n, 0);
    child = vvi(n);
    rep(i, 0, n - 1)
    {
        cin >> par[i + 1];
        par[i + 1]--;
        child[par[i + 1]].pb(i + 1);
        childcount[par[i + 1]]++;
    }
    queue<int> qu;
    rep(i, 0, n)
    {
        if (childcount[i] <= 0)
        {
            qu.push(i);
        }
        // sort(all(child[i]), cmp);
    }
    // vector<bool> proc(n, false);
    while (!qu.empty())
    {
        int k = qu.front();
        qu.pop();
        // if(proc[k]) continue;
        // proc[k] = true;
        if (k == 0)
            continue;
        subsz[par[k]] += subsz[k];
        childcount[par[k]]--;
        if (childcount[par[k]] <= 0)
        {
            qu.push(par[k]);
        }
    }
    rep(i, 0, n)
    {
        sort(all(child[i]), cmp);
    }
    pq.push({subsz[0], 0});
    sol = vi(n, -1);
    while (!pq.empty())
    {
        auto pv = pq.top();
        pq.pop();
        solve(pv.s);
        // cout << "yes" << nL;
    }
    cout << timer << nL;

    return 0;
}
