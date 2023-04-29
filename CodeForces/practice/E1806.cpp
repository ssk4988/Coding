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
using vvl = vector<vl>;

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
    int n, q; cin >> n >> q;
    vi par(n);
    vl arr(n);
    vi depth(n, -1);
    vi depthfreq(n);
    vvi child(n);
    rep(i, 0, n){
        cin >> arr[i];
    }
    par[0] = -1;
    depth[0] = 0;
    depthfreq[0] = 1;
    rep(i, 0, n - 1){
        cin >> par[i + 1];
        par[i + 1]--;
        child[par[i + 1]].pb(i + 1);
        depth[i + 1] = depth[par[i + 1]] + 1;
        depthfreq[depth[i + 1]]++;
    }
    int k = sqrt(n);
    int cnt = 0;
    // vector<unordered_map<int, int>> relabel(n);
    vi relabel(n);
    vvi depthbucket(n);
    rep(i, 0, n){
        if(depthfreq[depth[i]] <= k){
            relabel[i] = depthbucket[depth[i]].size();
            depthbucket[depth[i]].pb(i);
        }
    }
    vector<vvl> memo(n);
    rep(i, 0, n){
        memo[i] = vvl(depthbucket[i].size(), vl(depthbucket[i].size(), -1));
    }
    memo[0][0][0] = arr[0] * arr[0];
    // rep(i, 1, n){
    //     memo[i][i] = arr[i] * arr[i] + memo[par[i]][par[i]];
    // }
    rep(i, 0, q){
        int a, b; cin >> a >> b;
        a--,b--;
        vi ap, bp;
        ap.pb(a);
        bp.pb(b);
        while(ap.back() != 0 && (depthfreq[depth[ap.back()]] > k || memo[depth[ap.back()]][relabel[ap.back()]][relabel[bp.back()]] == -1)){
            ap.pb(par[ap.back()]);
            bp.pb(par[bp.back()]);
            // cout << ap.back() << " " << bp.back() << nL;
        }
        ll ans = memo[depth[ap.back()]][relabel[ap.back()]][relabel[bp.back()]];
        ap.pop_back();bp.pop_back();
        while(ap.size()){
            ans += arr[ap.back()] * arr[bp.back()];
            if(depthfreq[depth[ap.back()]] <= k){
                memo[depth[ap.back()]][relabel[ap.back()]][relabel[bp.back()]] = ans;
                memo[depth[ap.back()]][relabel[bp.back()]][relabel[ap.back()]] = ans;
                
            }
            ap.pop_back(); bp.pop_back();
        }
        cout << ans << nL;
    }
    
    return 0;
}