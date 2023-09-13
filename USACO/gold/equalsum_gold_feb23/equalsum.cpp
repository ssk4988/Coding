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
    vl v(n);
    rep(i, 0, n) cin >> v[i];
    vector<pair<ll, pi>> sums;
    rep(i, 0, n){
        ll sum = 0;
        rep(j, i, n){
            sum += v[j];
            sums.pb({sum, {i, j}});
        }
    }
    sort(all(sums));
    rep(i, 0, n){
        ll ans = LLONG_MAX;
        vl last(2, -1e18);
        for(auto [sum, idx] : sums){
            if(idx.f > i || idx.s < i){
                last[1] = sum;
            }
            else{
                last[0] = sum;
            }
            ans = min(ans, abs(last[0] - last[1]));
        }
        last = vl(2, 1e18);
        reverse(all(sums));
        for(auto [sum, idx] : sums){
            if(idx.f > i || idx.s < i){
                last[1] = sum;
            }
            else{
                last[0] = sum;
            }
            ans = min(ans, abs(last[0] - last[1]));
        }
        reverse(all(sums));
        cout << ans << nL;
    }
    
    return 0;
}