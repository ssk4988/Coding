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
    int n, k; cin >> n >> k;
    vl a(n);
    ll mx = 0;
    rep(i, 0, n){
        cin >> a[i];
        mx = max(mx, a[i]);
    }
    ll lo = mx, hi = 1e18;
    while(lo < hi){
        ll mid = lo + (hi - lo) / 2;
        ll k1 = 0;
        int l = 0, r = 0;
        ll sum = 0;
        while(l < n){
            while(r < n && sum + a[r] <= mid){
                sum += a[r];
                r++;
            }
            k1++;
            l = r;
            sum = 0;
        }
        if(k1 <= k){
            hi = mid;
        }
        else{
            lo = mid + 1;
        }
    }
    cout << lo << nL;
    
    return 0;
}
