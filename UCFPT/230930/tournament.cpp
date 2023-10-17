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
    int r = n;
    n = 1 << r;
    vi a(n);
    rep(i, 0, n) cin >> a[i];
    sort(all(a));
    reverse(all(a));
    int ans = 0;
    rep(j, 0, r){
        int ptr = 1 << j, lim = 1 << (j + 1);
        rep(i, 0, 1 << j){
            if(ptr < lim && a[i] - a[ptr] <= k){
                ans++;
                // cout << "pair " << a[i] << " with " << a[ptr] << nL;
                ptr++;
            }
        }
    }
    cout << ans << nL;
    
    return 0;
}