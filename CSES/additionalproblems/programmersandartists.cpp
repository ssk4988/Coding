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
    int a, b, n; cin >> a >> b >> n;
    vpi v(n);
    priority_queue<pi> pq;
    rep(i, 0, n){
        cin >> v[i].f >> v[i].s;
        pq.push({v[i].f, i});
        pq.push({v[i].s, i});
    }
    ll ans = 0;
    vi used(n);
    while(pq.size()){
        auto [v, i] = pq.top(); pq.pop();
        if(used[i]) continue;
        
    }
    // vector<pair<int, vi>> dp1(1 << n), dp2(1 << n);
    // vi amasks, bmasks;
    // rep(i, 0, 1 << n){
    //     if(__builtin_popcount(i) == a){
    //         pair<int, vi> sol;
    //         rep(j, 0, n){
    //             if((i >> j) & 1){
    //                 sol.s.pb(j);
    //                 sol.f += v[j].f;
    //             }
    //         }
    //         dp1[i] = max(dp1[i], sol);
    //         amasks.pb(i);     
    //     }
    //     if(__builtin_popcount(i) == b){
    //         pair<int, vi> sol;
    //         rep(j, 0, n){
    //             if((i >> j) & 1){
    //                 sol.s.pb(j);
    //                 sol.f += v[j].s;
    //             }
    //         }
    //         dp2[i] = max(dp2[i], sol);
    //         bmasks.pb(i);   
    //     }
    // }
    // int best = 0;
    // vpi bests;
    // for(int i : amasks){
    //     for(int j : bmasks){
    //         if(i & j) continue;
    //         int score = dp1[i].f + dp2[j].f;
    //         if(score > best){
    //             bests.clear();
    //         }
    //         if(score >= best){
    //             best = score;
    //             bests.pb({i, j});
    //         }
    //     }
    // }
    // cout << best << nL;
    // for(auto [i,j] : bests){
    //     cout << "Solution:\n";
    //     for(int i1 : dp1[i].s) cout << i1 << " ";
    //     cout << nL;
    //     for(int j1 : dp2[j].s) cout << j1 << " ";
    //     cout << nL;
    // }


    
    return 0;
}
