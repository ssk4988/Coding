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
    // vl a(n);
    map<ll, ll> best;
    ll pref = 0;
    best[pref] = 0;
    ll prevdp = 0;
    rep(i, 0, n){
        ll v; cin >> v;
        pref += v;
        ll dp = prevdp - 1;
        auto it = best.upper_bound(pref);
        if(it != best.begin()){
            it = prev(it);
            dp = max(dp, it->s);
        }
        prevdp = dp;
        it = best.upper_bound(pref);
        if(it == best.begin() || prev(it)->s < dp) {
            best[pref] = dp;
            while(true){
                it = best.upper_bound(pref);
                if(it == best.end() || it->s > dp) break;
                best.erase(it);
            }
        }
    }
    cout << n + prevdp << "\n";
    
    return 0;
}
