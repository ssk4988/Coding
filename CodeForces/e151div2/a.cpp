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
        int n, k, x; cin >> n >> k >> x;
        if(x != 1){
            cout << "YES\n";
            cout << n << nL;
            rep(i, 0, n){
                cout << 1 << " ";
            }
            cout << nL;
        }
        else{
            if(k == 1) cout << "NO\n";
            else if(k == 2) {
                cout << (n % 2 == 0 ? "YES" : "NO") << nL;
                if(n % 2 == 0){
                    cout << n / 2 << nL;
                    rep(i, 0, n / 2){
                        cout << 2 << " " ;
                    }
                    cout << nL;
                }
            }
            else{ 
                cout << (n > 1 ? "YES" : "NO") << nL;
                if(n % 2 == 0){
                     cout << n / 2 << nL;
                    rep(i, 0, n / 2){
                        cout << 2 << " " ;
                    }
                    cout << nL;
                }
                else{
                    vi ans;
                    while(n > 3){
                        ans.pb(2);
                        n -= 2;
                    }
                    ans.pb(3);
                    cout << sz(ans) << nL;
                    for(int i : ans){
                        cout << i << " ";
                    }
                    cout << nL;
                }
            }
        }
    }
    
    return 0;
}
