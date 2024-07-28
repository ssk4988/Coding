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
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int k; cin >> k;
        vvi qs(30);
        rep(t, 0, k){
            int n; cin >> n;
            qs[__lg(n)].pb(n);
            // pq.push(n);
            rep(_, 0, n-1){
                int v; cin >> v;
            }
        }
        int ans = 0;
        for(int b = sz(qs)-1; b >= 0; b--) {
            for(int x : qs[b]){
                int cur = -1;
                if((ans >> b) & 1) {
                    cur = (1 << b) - 1;
                } else {
                    ans |= 1 << b;
                    cur = x - (1 << b);
                }
                if(cur) {
                    qs[__lg(cur)].pb(cur);
                }
            }
        }
        // while(!pq.empty()){
        //     int x = pq.top(); pq.pop();
        //     if(x == 0) continue;
        //     int bit = __lg(x);
        //     if(bit & ans) {
        //         x = bit-1;
        //         pq.push()
        //     }
        // }
        cout << ans << "\n";
    }
    
    return 0;
}
