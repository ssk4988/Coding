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
        int n; ll k; cin >> n >> k;
        vl f(n), d(n), p(n);
        rep(i, 0, n) cin >> f[i];
        rep(i, 0, n) cin >> d[i];
        rep(i, 0, n) p[i] = f[i] * d[i];
        int ans = n;
        rep(i, 0, n){
            vvi occ(2 * k + 1);
            ll lef = p[i] - k;
            rep(j, 0, n){
                set<ll> ds;
                if(abs(p[j] - p[i]) <= k){
                    ds.insert(d[j]);
                    // occ[p[j] - lef].pb(j);
                }
                if(abs((p[i] / f[j]) * f[j] - p[i]) <= k){
                    ds.insert(p[i] / f[j]);
                    // occ[(p[i] / f[j]) * f[j] - lef].pb(j);
                }
                if(abs(((p[i] / f[j]) + 1) * f[j] - p[i]) <= k){
                    ds.insert((p[i] / f[j]) + 1);
                    // occ[((p[i] / f[j]) + 1) * f[j] - lef].pb(j);
                }
                for(ll d1 : ds){
                    if(d1 <= 0) continue;
                    occ[d1 * f[j] - lef].pb(j);
                }
            }
            vi cnt(n);
            int numunchanged = 0;
            int inwindow = 0;
            rep(j, 0, sz(occ)){
                for(int idx : occ[j]){
                    cnt[idx]++;
                    if(cnt[idx] == 1){
                        inwindow++;
                    }
                    if(p[idx] == j + lef){ 
                        numunchanged++;
                    }
                }
                if(j >= k + 1){
                    for(int idx : occ[j - (k + 1)]){
                        cnt[idx]--;
                        if(cnt[idx] == 0) inwindow--;
                        if(p[idx] == j - (k + 1) + lef){
                            numunchanged--;
                        }
                    }
                }
                assert(inwindow <= n);
                assert(numunchanged <= n);
                assert(inwindow >= 0);
                assert(numunchanged >= 0);
                if(inwindow == n){
                    ans = min(ans, n - numunchanged);
                }
            }
        }
        cout << ans << nL;
    }
    
    return 0;
}