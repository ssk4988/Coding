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
        int n, k; cin >> n >> k;
        int first = 0, last = n - 1;
        vi ans;
        rep(i, 0, k){
            int dif = n / k + (i < (n % k));
            if(i & 1){
                ans.pb(last);
                last -= dif;
            }
            else{
                ans.pb(first);
                first += dif;
            }
        }
        rep(i, k, n){
            ans.pb(ans[i - k] + (((i % k) & 1) ? -1 : 1));
        }
        for(int i : ans){
            cout << (i+1) << " ";
        }
        cout << nL;
    }
    
    return 0;
}
