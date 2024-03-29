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
        int n, q; cin >> n >> q;
        vi divs;
        vl a(n);
        vector<vl> equiv;
        rep(i, 0, n){
            cin >> a[i];
        }
        multiset<ll> best;
        vi divs1;
        rep(i, 1, n){
            if(n % i == 0){
                divs1.pb(i);
            }
        }
        for(int i : divs1){
            bool good = true;
            for(int j : divs1){
                if(i == j) continue;
                if(j % i == 0) good = false;
            }
            if(good){
                divs.pb(i);
                equiv.pb(vl(i));
                rep(j, 0, i){
                    for(int k = j, c = 0; c < n / i; c++, k = (k + i) % n){
                        equiv.back()[j] += a[k];
                    }
                    equiv.back()[j] *= i;
                    best.insert(equiv.back()[j]);
                }
            }
        }
        // rep(i, 1, n){
        //     if(n % i == 0){
        //     }
        // }
        cout << *best.rbegin() << "\n";
        rep(_, 0, q){
            int p; ll x; cin >> p >> x; p--;
            rep(i, 0, sz(divs)){
                best.erase(best.find(equiv[i][p % divs[i]]));
                equiv[i][p % divs[i]] -= a[p] * divs[i];
                equiv[i][p % divs[i]] += x * divs[i];
                best.insert(equiv[i][p % divs[i]]);
            }
            a[p] = x;
            cout << *best.rbegin() << "\n";
        }
    }
    
    return 0;
}
