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
    int n, m; cin >> n >> m;
    vi a(n), inv(n);
    rep(i, 0, n){
        cin >> a[i];
        a[i]--;
        inv[a[i]] = i;
    }
    vvi adj(n);
    vpi v(m);
    int BAD = n + 5;
    vi nex(n, n - 1), pre(n, 0);
    rep(i, 0, m){
        cin >> v[i].f >> v[i].s;
        v[i].f--;v[i].s--;
        adj[v[i].f].pb(v[i].s);
        adj[v[i].s].pb(v[i].f);
    }
    rep(i, 0, n){
        for(int j : adj[i]){
            if(inv[j] > inv[i]){
                nex[inv[i]] = min(nex[inv[i]], inv[j] - 1);
            }
            if(inv[j] < inv[i]){
                pre[inv[i]] = max(pre[inv[i]], inv[j] + 1);
            }
        }
    }
    int r = 0;
    multiset<int> nexset, preset;
    nexset.insert(n + 5);
    ll ans = 0;
    rep(l, 0, n){
        // while(r < l){
        //     nexset.erase(nexset.find(nex[r]));
        //     preset.erase(preset.find(pre[r]));
        //     r++;
        // }
        while(r < n && pre[r] <= l && r <= nex[r] && r <= (*nexset.begin())){
            preset.insert(pre[r]);
            nexset.insert(nex[r]);
            r++;
        }
        ans += r - l;
        nexset.erase(nexset.find(nex[l]));
        preset.erase(preset.find(pre[l]));
    }
    cout << ans << nL;
    
    return 0;
}