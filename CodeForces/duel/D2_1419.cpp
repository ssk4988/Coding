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
    vi a(n);
    rep(i, 0, n){
        cin >> a[i];
    }
    sort(all(a));
    vi ans;
    int l = 0, r = n / 2;
    for(int i = 0; i < n; i++){
        if(i & 1){
            ans.pb(a[l++]);
        }
        else ans.pb(a[r++]);
    }
    int v = 0;
    rep(i, 1, n - 1){
        if(ans[i] < ans[i - 1] && ans[i] < ans[i + 1]) v++;
    }
    cout << v << "\n";
    for(int i : ans) cout << i << " ";
    cout << "\n";
    
    return 0;
}