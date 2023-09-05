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
        int n, k, x; cin >> n >> k >> x;
        int sum = 0;
        rep(i, 1, n + 1) sum ^= i;
        if((k % 2 == 0 && sum != 0) || (k % 2 == 1 && sum != x)){
            cout << "NO\n";
            continue;
        }
        vvi sols;
        vi used(n + 1);
        if(x <= n){
            used[x] = true;
            sols.pb({x});
        }
        rep(i, 1, n + 1){
            if(used[i]) continue;
            int other = i ^ x;
            if(other > 0 && other <= n && !used[other]){
                sols.pb({i, other});
                used[i] = used[other] = true;
            }
        }
        vi z;
        int zv = 0;
        rep(i, 1, n + 1){
            if(!used[i]){
                z.pb(i);
                zv ^= i;
            }
        }
        if(zv == x){
            sols.pb(vi(z));
            z.clear();
        }
        if(sz(sols) < k){
            cout << "NO\n";
            continue;
        }
        if(sz(z)){
            for(int i : z) sols.back().pb(i);
        }
        while(sz(sols) > 2 && sz(sols) > k){
            auto v1 = sols.back(); sols.pop_back();
            auto v2 = sols.back(); sols.pop_back();
            for(int i : v1) sols.front().pb(i);
            for(int i : v2) sols.front().pb(i);
        }
        if(sz(sols) != k){
            cout << "NO\n";
        }
        else{
            cout << "YES\n";
            for(auto &v : sols){
                cout << sz(v) << " ";
                for(int i : v) cout << i << " ";
                cout << nL;
            }
            
        }
    }
    // int x = 0;
    // rep(i, 1, 40){
    //     x ^= i;
    //     cout << i << " " << x << nL;
    // }
    
    return 0;
}
