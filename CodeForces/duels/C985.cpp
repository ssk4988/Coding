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
    int n,k,l; cin >> n >> k >> l;
    vi a(n * k);
    rep(i, 0, n * k) cin >> a[i];
    sort(all(a));
    if(n == 1){
        cout << a[0] << nL;
        return 0;
    }
    int other = 0;
    while(other < n * k && abs(a[0] - a[other]) <= l) other++;
    vi used(n * k);
    if(abs(a[other-1] - a[0]) > l || other < n){
        cout << 0 << nL;
        return 0;
    }
    ll ans = 0;
    int cur = 0;
    int numused = 0;
    rep(i, 0, n * k){
        if(numused >= n) break;
        if(cur >= k) {
            cur = 0;
        }
        if(cur == 0){
            numused++;
            ans += a[i];
        }
        else if(n - numused + i == other){
            rep(j, i, other){
                ans += a[j];
            }
            break;
        }
        cur++;
    }
    cout << ans << nL;
    return 0;
}
