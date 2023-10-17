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
        int n; cin >> n;
        multiset<ll> freq;
        rep(i, 0, 2 * n - 1){
            ll k; cin >> k;
            freq.insert(k);
        }
        if(n == 1){
            cout << "Case #" << (cn + 1) << ": " << 1 << "\n";
            continue;
        }
        auto cpy = [](multiset<ll> &f)->multiset<ll> {
            multiset<ll> res;
            for(ll k : f) res.insert(k);
            return res;
        };
        ll ans = LLONG_MAX;
        {
            // between
            multiset<ll> freq1 = cpy(freq);
            auto mn = *freq1.begin(), mx = *freq1.rbegin();
            ll sum = mn + mx;
            vl nopair;
            while(sz(freq1) >= 2){
                ll t = *freq1.begin();
                freq1.erase(freq1.begin());
                if(freq1.find(sum - t) != freq1.end()){
                    freq1.erase(freq1.find(sum - t));
                }
                else{
                    nopair.pb(t);
                }
            }
            for(ll k : freq1) nopair.pb(k);
            if(sz(nopair) == 1 && sum - nopair[0] > 0){
                ans = min(ans, sum - nopair[0]);
            }
        }
        {
            // <= min
            multiset<ll> freq1 = cpy(freq);
            ll realmx = *freq1.rbegin();
            freq1.erase(freq1.find(realmx));
            auto mn = *freq1.begin(), mx = *freq1.rbegin();
            ll sum = mn + mx;
            vl nopair;
            while(sz(freq1) >= 2){
                ll t = *freq1.begin();
                freq1.erase(freq1.begin());
                if(freq1.find(sum - t) != freq1.end()){
                    freq1.erase(freq1.find(sum - t));
                }
                else{
                    nopair.pb(t);
                }
            }
            for(ll k : freq1) nopair.pb(k);
            if(sz(nopair) == 0 && sum - realmx > 0){
                ans = min(ans, sum - realmx);
            }
        }
        {
            // >= mx
            multiset<ll> freq1 = cpy(freq);
            ll realmn = *freq1.begin();
            freq1.erase(freq1.find(realmn));
            auto mn = *freq1.begin(), mx = *freq1.rbegin();
            ll sum = mn + mx;
            vl nopair;
            while(sz(freq1) >= 2){
                ll t = *freq1.begin();
                freq1.erase(freq1.begin());
                if(freq1.find(sum - t) != freq1.end()){
                    freq1.erase(freq1.find(sum - t));
                }
                else{
                    nopair.pb(t);
                }
            }
            for(ll k : freq1) nopair.pb(k);
            if(sz(nopair) == 0 && sum - realmn > 0){
                ans = min(ans, sum - realmn);
            }
        }
        if(ans == LLONG_MAX) ans = -1;
        cout << "Case #" << (cn + 1) << ": " << ans << "\n";
    }
    
    return 0;
}
