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
    int maxval = 1'000'100;
    vi composite(maxval);
    composite[0] = composite[1] = true;
    for(int i = 4; i < maxval; i += 2) composite[i] = true;
    vi primes;
    primes.pb(2);
    for(int i = 3; i < maxval; i += 2){
        if(!composite[i]){
            primes.pb(i);
            for(ll v = ll(i) * i; v < maxval; v += i){
                composite[v] = true;
            }
        }
    }
    int nc; cin >> nc;
    rep(cn, 0, nc){
        ll r, c; cin >> r >> c;
        ll rc = r * c;
        if(composite[r] || composite[c]){
            int v = 1;
            vvi ans(r, vi(c));
            if(composite[c]){
                rep(j, 0, r){
                    rep(i, 0, c){
                        ans[j][i] = v;
                        v++;
                    }
                }
            }
            else{
                rep(i, 0, c){
                    rep(j, 0, r){
                        ans[j][i] = v;
                        v++;
                    }
                }
            }
            rep(i, 0, r){
                rep(j, 0, c){
                    cout << ans[i][j] << " ";
                }
                cout << nL;
            }
            continue;
        }
        rep(i, 0, r){
            int rownum = ((2 * i) % r);
            rep(j, 0, c){
                cout << (j + 1 + c * rownum) << " ";
            }
            cout << nL;
        }
    }
    
    return 0;
}
