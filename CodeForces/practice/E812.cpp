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
    int n; cin >> n;
    vl a(n);
    rep(i, 0, n){
        cin >> a[i];
    }
    vi parent(n);
    vvi child(n);
    rep(i, 1, n){
        cin >> parent[i]; parent[i]--;
        child[parent[i]].pb(i);
    }
    // cout << "got here" << endl;
    vi parity(n, -1);
    auto dfs = [&](int u, int d, auto &&dfs) -> void {
        if(parity[u] != -1) return;
        // cout << "dfs on " << u << endl;
        parity[u] = d;
        dfs(parent[u], d ^ 1, dfs);
    };
    vector<map<ll, ll>> frq(2);
    vl sm(2);
    ll sum = 0;
    rep(i, 0, n){
        // cout << i << " " << parent[i] << endl;
    }
    rep(i, 0, n){
        // cout << i << " " << parent[i] << " " << parity[i] << " " << a[i] << endl;
        if(sz(child[i]) == 0) dfs(i, 1, dfs);
    }
    rep(i, 0, n){
        if(parity[i]) sum ^= a[i];
        frq[parity[i]][a[i]]++;
        sm[parity[i]]++;
    }
    // cout << "got here" << endl;
    ll ans = 0;
    if(sum == 0){
        for(auto [v, f] : frq[0]){
            // ans += f * (f-1) / 2;
            ans += f * frq[1][v];
        }
        // for(auto [v, f] : frq[1]){
        //     ans += f * (f-1) / 2;
        // }
        ans += sm[0] * (sm[0]-1) / 2;
        ans += sm[1] * (sm[1]-1) / 2;
    }
    else{
        for(auto [v, f] : frq[0]){
            // ans += f * (f-1) / 2;
            ans += f * frq[1][v^sum];
        }
    }
    cout << ans << "\n";


    
    return 0;
}
