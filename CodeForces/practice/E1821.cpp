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

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc;
    cin >> nc;
    rep(cn, 0, nc)
    {
        int k;
        cin >> k;
        string str;
        cin >> str;
        vvi adj(1);
        vi par(1, -1), dep(1, -1), subsz(1, 1);
        int cur = 0;
        rep(i, 0, sz(str))
        {
            if (str[i] == '(')
            {
                int nex = sz(adj);
                adj.pb({});
                subsz.pb(1);
                dep.pb(1 + dep[cur]);
                par.pb(cur);
                adj[cur].pb(nex);
                cur = nex;
            }
            else
            {
                subsz[par[cur]] += subsz[cur];
                cur = par[cur];
            }
        }
        ll curans = 0;
        priority_queue<pi> pq;
        rep(i, 1, sz(adj))
        {
            curans += dep[i];
            if(subsz[i] > 1) pq.push({subsz[i] - 1, i});
        }
        rep(i, 0, k){
            if(pq.size()){
                pi p = pq.top(); pq.pop();
                curans -= p.f;
            }
        }
        cout << curans << nL;
    }

    return 0;
}
