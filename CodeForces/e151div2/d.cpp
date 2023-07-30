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
        vl a(n);
        rep(i, 0, n) cin >> a[i];
        vl pref(a), suff(a);
        for(int i = 1; i < n; i++) pref[i] += pref[i - 1];
        for(int i = n - 2; i >= 0; i--) suff[i] += suff[i + 1];
        pl best = {0, 0};
        int mindex = n - 1;
        for(int i = n - 1; i >= 0; i--){
            if(pref[i] < pref[mindex]) mindex = i;
            ll t = pref[i];
            if(mindex + 1 < n) t += suff[mindex + 1];
            if(t > best.f){
                best = {t, pref[i]};
            }
        }
        ll t = 0;
        if(mindex + 1 < n) t += suff[mindex + 1];
        if(t > best.f){
            best = {t, 0};
        }
        // best = max({t, 0}, best);
        cout << best.s << nL;
        // also just try for m = 0
    }
    
    return 0;
}
