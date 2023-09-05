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
        vi a(n);
        rep(i, 0, n){
            cin >> a[i];
        }
        bool found = false;
        rep(i, 0, n){
            bool hasdiv = false;
            rep(j, 0, n){
                if(a[j] % a[i] == 0 && a[j] != a[i]) hasdiv = true;
            }
            if(!hasdiv){
                vi b, c;
                rep(j, 0, n){
                    if(a[i] == a[j]) c.pb(a[j]);
                    else b.pb(a[j]);
                }
                if(sz(b) == 0 || sz(c) == 0) continue;
                found = true;
                cout << sz(b) << " " << sz(c) << nL;
                for(int j : b) cout << j << " ";
                cout << nL;
                for(int j : c) cout << j << " ";
                cout << nL;
                break;
            }
        }
        if(!found){
            cout << "-1\n";
        }
    }
    
    return 0;
}
