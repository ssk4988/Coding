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
    int sq = 0;
    set<int> bd;
    rep(i, 1, 2000){
        int s = (int)(sqrt(i));
        if(s * s == i) sq++;
        if(i/5 < sq){
            bd.insert(i);
        }
    }
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n, m; cin >> n >> m;
        vpi ed(m);
        rep(i, 0, m){
            cin >> ed[i].f >> ed[i].s; ed[i].f--, ed[i].s--;
        }
        if(!bd.count(n)){
            cout << n << nL;
            rep(i, 0, n) cout << (i + 1) << " ";
            cout << nL;
            continue;
        }
        vi adj(n);
        for(auto [u, v] : ed){
            adj[u] ^= 1 << v;
        }
        vi tog(n);
        rep(i, 0, n){
            for(int j = i + 1; j <= n; j += i + 1){
                tog[i] ^= 1 << (j-1);
            }
        }
        int req = n / 5;
        int found = 0;
        auto test = [&](int used, int pre, int mask, auto &&test) -> void {
            if(found) return;
            if(used >= 1 && used <= req){
                bool valid = true;
                int mask1 = mask;
                int flp = 0;
                rep(i, 0, n){
                    if((mask1 >> i) & 1){
                        flp ^= 1 << i;
                        mask1 ^= tog[i];
                    }
                }
                rep(i, 0, n){
                    if((flp >> i) & 1){
                        if((flp & adj[i]) != adj[i]){
                            valid = false;
                            break;
                        }
                    }
                }
                if(valid) found = flp;
            }
            if(used == req) return;
            rep(i, pre + 1, n){
                test(used + 1, i, mask ^ (1 << i), test);
            }
        };
        test(0, -1, 0, test);
        if(!found){
            cout << -1 << nL;
        }
        else{
            cout << __builtin_popcount(found) << nL;
            rep(i, 0, n){
                if((found >> i) & 1) cout << (i + 1) << " ";
            }
            cout << nL;
        }
    }
    
    return 0;
}
