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
    vi ans(10001);
    ans[1] = 1;
    auto nex = [](int v)->int{
        int res = 0;
        while(v){
            res += (v % 10) * (v % 10);
            v /= 10;
        }
        return res;
    };
    rep(i, 2, sz(ans)){
        set<int> path;
        int cur = i;
        while(ans[cur] == 0 && path.count(cur) == 0){
            path.insert(cur);
            cur = nex(cur);
        }
        if(ans[cur] != 0){
            for(int i : path){
                ans[i] = ans[cur];
            }
        }
        else{
            for(int i : path){
                ans[i] = -1; // cycle
            }
        }

    }
    vi c(10001);
    c[0] = c[1] = true;
    rep(j, 2, sz(c)){
        if(!c[j]){
            for(int k = j * j; k < sz(c); k += j) c[k] = true;
        }
    }
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int k, v; cin >> k >> v;
        cout << k << " " << v << " " << (!c[v] && ans[v] == 1 ? "YES" : "NO") << nL;
    }
    
    return 0;
}
