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
    vector<bool> composite(10'000'005);
    composite[0] = composite[1] = true;
    vi primes;
    vvi ans(n, vi(2, -1));
    int sq = sqrt(10'000'100);
    rep(i, 2, sz(composite)){
        if(!composite[i]){
            if(i >= sq){
                continue;
            }
            primes.pb(i);
            for(int j = i * i; j < sz(composite); j += i){
                composite[j] = true;
            }
        }
    }
    // cout << sz(primes) << nL;
    rep(i, 0, n){
        int a; cin >> a;
        int a1 = a;
        if(a % 2 == 0){
            while(a1 % 2 == 0){
                a1 /= 2;
            }
            if(a1 != 1){
                ans[i][0] = 2;
                ans[i][1] = a1;
            }
        }
        else{
            vi pf;
            for(int p : primes){
                if(a1 < p) break;
                if(a1 % p == 0){
                    pf.pb(p);
                    while(a1 % p == 0){
                        a1 /= p;
                    }
                    if(pf.size() >= 2) break;
                }
            }
            if(a1 > 1){
                pf.pb(a1);
            }
            if(pf.size() >= 2){
                ans[i][0] = pf[0];
                ans[i][1] = pf[1];
            }
        }
        if(ans[i][0] != -1 && gcd(ans[i][0] + ans[i][1], a) != 1){
            ans[i][0] = ans[i][1] = -1;
        }
    }
    rep(i, 0, n){
        cout << ans[i][0] << " ";
    }
    cout << nL;
    rep(i, 0, n){
        cout << ans[i][1] << " ";
    }
    cout << nL;
    
    return 0;
}
