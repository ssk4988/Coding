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
    int n, q; cin >> n >> q;
    vl a(n);
    rep(i, 0, n){
        cin >> a[i];
    }
    ll sum = accumulate(all(a), 0LL);
    set<ll> diff;
    rep(i, 0, n) diff.insert(i);
    ll s = -1;
    rep(_, 0, q){
        int t; cin >> t;
        if(t == 1){
            int i, x; cin >> i >> x; i--;
            if(!diff.count(i)){
                a[i] = s;
                diff.insert(i);
            }
            sum -= a[i];
            a[i] = x;
            sum += a[i];
        }
        else{
            diff.clear();
            ll x; cin >> x;
            sum = x * n;
            s = x;
        }
        cout << sum << "\n";
    }
    
    return 0;
}
