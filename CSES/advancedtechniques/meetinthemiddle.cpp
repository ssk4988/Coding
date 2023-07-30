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
    ll x; cin >> x;
    vl a(n);
    rep(i, 0, n) cin >> a[i];
    vector<vl> b(2);
    rep(i, 0, n/2){
        b[0].pb(a[i]);
    }
    rep(i, n/2, n){
        b[1].pb(a[i]);
    }
    // vector<unordered_map<ll, ll>> freq(2);
    vector<vl> sums(2);
    vector<vpl> sp(2);
    rep(i, 0, 2){
        int k = sz(b[i]);
        rep(j, 0, 1 << k){
            ll sum = 0;
            rep(l, 0, k){
                if(j & (1 << l)) sum += b[i][l];
            }
            // freq[i][sum]++;
            sums[i].pb(sum);
        }
        sort(all(sums[i]));
        int j = 0;
        while(j < sz(sums[i])){
            int cnt = 1;
            j++;
            while(j < sz(sums[i]) && sums[i][j] == sums[i][j - 1]){
                cnt++;
                j++;
            }
            sp[i].pb({sums[i][j - 1], cnt});
        }
    }
    reverse(all(sp[1]));

    ll ans = 0;
    int idx = 0;
    for(auto [sum, freq] : sp[0]){
        while(idx < sz(sp[1]) && sum + sp[1][idx].f > x) idx++;
        if(idx < sz(sp[1]) && sp[1][idx].f + sum == x){
            ans += freq * sp[1][idx].s;
        }
    }
    // for(auto [key, val] : freq[0]){
    //     ans += val * (freq[1].count(x - key) ? freq[1][x - key] : 0);
    // }
    cout << ans << nL;
    
    return 0;
}