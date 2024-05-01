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
        int ok = k;
        vi ans;
        vi make(n + 1);
        make[0] = 1;
        int cant = 0;
        k--;
        for(int b = 1; k > 0; b *= 2){
            int add = min(b, k);
            k -= add;
            ans.pb(add);
        }
        for(int i : ans){
            for(int j = sz(make) - 1; j >= 0; j--){
                if(j - i >= 0 && make[j-i]){
                    make[j] = 1;
                }
            }
        }
        while(cant < sz(make) && make[cant]) cant++;
        assert(cant == ok);
        cant++;
        while(cant <= n){
            ans.pb(cant);
            for(int j = sz(make) - 1; j >= 0; j--){
                if(j - cant >= 0 && make[j-cant]){
                    make[j] = 1;
                }
            }
            while(cant < sz(make) && make[cant]) cant++;
        }
        assert(sz(ans) <= 25);
        cout << sz(ans) << nL;
        for(int i : ans) cout << i << " ";
        cout << nL;
    }
    
    return 0;
}
