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
    vi done(n);
    vpi adj(m);
    rep(i, 0, m){
        int a, b; cin >> a >> b; a--, b--;
        if(a > b) swap(a, b);
        adj[i] = {a, b};
    }
    vi perm(n, -1);
    rep(i, 0, n){
        vi indeg(n), outdeg(n);
        for(auto [a, b] : adj){
            if(done[a] || done[b]) continue;
            indeg[b]++;
            outdeg[a]++;
        }
        int seen = 0;
        rep(j, 0, n){
            if(done[j]) continue;
            // cout << i << " " << j << " " << indeg[j] << " " << seen << nL;
            if(seen == indeg[j] && outdeg[j] == 0){
                perm[j] = i;
                done[j] = true;
                break;
            }
            if(!done[j]) seen++;
        }
    }
    vl dp(n + 2);
    perm.push_back(n + 1);
    dp[0] = 1;
    rep(i, 0, n + 1){
        int maxsofar = n + 5;
        rep(j, i+1, n+2){
            if(perm[j - 1] < maxsofar && perm[j - 1] > (i == 0 ? -1 : perm[i - 1])){
                dp[j] += dp[i];
                maxsofar = min(maxsofar, perm[j - 1]);
            }
        }
    }
    cout << dp.back() << nL;
    
    return 0;
}
