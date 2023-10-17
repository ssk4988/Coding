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
        sort(all(a));
        if(n == 1){
            cout << a[0] << nL;
            continue;
        }
        ll sum = 0;
        rep(i, 0, n) sum += a[i];
        ll left = a[n/2-1], right = a[n/2];
        set<ll> sols;
        if(left * (n + 1) - sum <= left){
            sols.insert(left * (n + 1) - sum);
        }
        if(right * (n + 1) - sum >= right){
            sols.insert(right * (n + 1) - sum);
        }
        if(sum % n == 0){
            ll mid = sum / n;
            if(left <= mid && mid <= right) sols.insert(mid);
        }
        cout << *sols.begin() << nL;
    }
    
    return 0;
}
