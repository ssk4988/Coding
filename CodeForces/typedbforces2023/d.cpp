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

struct DSU
{
    vi parent;
    vi siz;
    DSU(int n) : parent(n), siz(n, 1)
    {
        rep(i, 0, n)
        {
            parent[i] = i;
        }
    }
    int find(int a)
    {
        if (parent[a] == a)
        {
            return a;
        }
        return parent[a] = find(parent[a]);
    }

    void join(int a, int b)
    {
        a = find(a);
        b = find(b);
        if (a == b)
            return;
        parent[b] = a;
        siz[a] += siz[b];
    }

    int get_siz(int a)
    {
        return siz[find(a)];
    }
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc;
    cin >> nc;
    rep(cn, 0, nc)
    {
        int n;
        cin >> n;
        vi a(n);
        vi nex(n);
        DSU cycle(n + 1), cycle1(n + 1);
        rep(i, 0, n)
        {
            cin >> a[i];
            nex[i] = a[i] + i;
            if (nex[i] < 0 || nex[i] >= n)
                nex[i] = n;
            cycle.join(nex[i], i);
            if (i > 0)
                cycle1.join(nex[i], i);
        }
        bool oneout = cycle.find(0) == n;
        int numout = cycle.get_siz(n) - 1;
        set<int> path1;
        int k = 0;
        while (k >= 0 && k < n && path1.find(k) == path1.end())
        {
            path1.insert(k);
            k = nex[k];
        }
        vi path0;
        k = 0;
        while (path0.size() < path1.size())
        {
            path0.pb(k);
            k = nex[k];
        }
        ll ans = 0;
        rep(i, 1, n)
        {
            if (path1.find(i) == path1.end())
            {
                int curans = 0;
                curans = oneout ? 2 * n + 1 : 0;
                ans += curans;
            }
        }
        vi uc(n), nested(n); //unsolved children
        rep(i, 0, n){
            if(nex[i] < n && cycle.find(i) == n) uc[nex[i]]++;
        }
        queue<int> q;
        rep(i, 0, n){
            if(uc[i] == 0 && cycle.find(i) == n){
                q.push(i);
            }
        }
        while(!q.empty()){
            int p = q.front(); q.pop();
            if(nex[p] == n) continue;
            nested[nex[p]] += 1 + nested[p];
            uc[nex[p]]--;
            if(uc[nex[p]] == 0) q.push(nex[p]);
        }
        rep(i, 0, path0.size())
        {
            int curans = n + 1;
            if (oneout)
            {
                // trouble case:
                curans += numout - (nested[path0[i]] + 1);
            }
            else{
                curans += numout;
            }
            ans += curans;
        }
        cout << ans << nL;
    }

    return 0;
}
