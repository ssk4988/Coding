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
    int n, x;
    cin >> n >> x;
    vi a(n);
    rep(i, 0, n){
        cin >> a[i];
    }
    int ans = 0;
    sort(all(a));
    int l = 0, r = n - 1;
    while(l <= r){
        if(a[l] + a[r] <= x){
            l++;r--;
        }
        else{
            r--;
        }
        ans++;
    }
    cout << ans << nL;
    
    return 0;
}
