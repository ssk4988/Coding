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
        ll n, k; cin >> n >> k;
        ll prod = 1;
        vl a(n);
        rep(i, 0, n){
            cin >> a[i];
            prod *= a[i];
        }
        if(2023 % prod != 0){
            cout << "NO\n";
        }
        else{
            cout << "YES\n";
            cout << (2023 / prod) << " ";
            rep(i, 1, k){
                cout << 1 << " ";
            }
            cout << nL;
        }
    }
    
    return 0;
}
