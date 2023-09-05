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
    // cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    vi composite(8000);
    composite[0] = composite[1] = true;
    vector<unordered_map<int, int>> pfs(8000), sums(8000);
    vi primes;
    rep(i, 2, sz(composite)){
        if(!composite[i]){
            primes.pb(i);
            for(int j = i * i; j < sz(composite); j += i){
                composite[j] = true;
            }
        }
    }
    rep(i, 2, sz(composite)){
        int v = i;
        for(int p : primes){
            while(v % p == 0){
                pfs[i][p]++;
                v /= p;
            }
        }
    }
    // cout << "done precomp factors" << nL;
    // rep(i, 2, sz(sums)){
    //     for(auto [key, val] : sums[i - 1]){
    //         sums[i][key] += val;
    //     }
    //     for(auto [key, val] : pfs[i]){
    //         sums[i][key] += val;
    //     }
    // }
    // cout << "precomp answers" << nL;
    rep(i, 0, nc){
        int n; cin >> n;
        map<int, int> ans;
        rep(j, 2, n + 1){
            for(auto [key, val] : pfs[j]){
                ans[key] += val;
            }
        }
        for(auto [key, val] : ans){
            cout << val << " ";
        }
        cout << nL;
    }
    
    return 0;
}
