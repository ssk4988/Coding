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

const int DIF = 1e5;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    ll w; cin >> w;
    vl c(8);
    rep(i, 0, 8) cin >> c[i];
    ll target = max(0LL, w - DIF);
    ll cur = 0;
    for(int i = 7; i >= 0; i--){
        ll add = min(c[i], (target - cur) / (i+1));
        c[i] -= add;
        cur += (i+1) * add;
    }
    ll dif = w - cur;
    // cout << "dif: " << dif << endl;
    vl items;
    rep(i, 0, 8){
        for(ll p = min(c[i], 1LL); c[i]; p = min(c[i], 2 * p)){
            items.pb(p * (i+1));
            c[i] -= p;
        }
    }
    bitset<DIF+100> bs;
    bs[0] = true;
    for(auto x : items){
        if(x > dif) continue;
        // cout << "item: " << x << "\n";
        bs |= bs << x;
    }
    ll best = 0;
    rep(i, 0, dif+1){
        if(bs[i]) best = max(best, (ll)i);
    }
    // cout << "best add: " << best << " to " << cur << "\n";
    best = cur + best;
    cout << best << "\n";
    
    return 0;
}