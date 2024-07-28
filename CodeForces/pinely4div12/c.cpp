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
        rep(i, 0, n){
            cin >> a[i];
        }
        if(n == 1){
            cout << 1 << "\n";
            cout << a[0] << "\n";
            continue;
        }
        vl ans;
        sort(all(a));
        bool works = true;
        while(a[0] != 0 || a[n-1] != 0){
            if((a[0] + a[n-1]) % 2 != 0){
                works = false;
                break;
            }
            ll x = (a[0] + a[n-1]) / 2;
            ans.pb(x);
            rep(i, 0, n){
                a[i] = abs(a[i] - x);
            }
            sort(all(a));
        }
        assert(sz(ans) <= 40);
        if(works){
            cout << sz(ans) << "\n";
            for(auto x : ans){
                cout << x << " ";
            }
            cout << "\n";
        }
        else{
            cout << "-1\n";
        }
    }
    
    return 0;
}
