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
    // int N = 1000;
    // vi dp(N);
    // rep(i, 1, N){
    //     rep(j, 0, i){
    //         if((i ^ j) < i){
    //             if(!dp[j] && !dp[i ^ j]){
    //                 dp[i] = true;
    //             }
    //         }
    //     }
    // }
    // cout << "winners\n";
    // rep(i, 0, 20){
    //     if(dp[i]){
    //         cout << bitset<10>(i) << nL;
    //     }
    // }
    // cout << "losers\n";
    // rep(i, 1, 50){
    //     if(!dp[i]){
    //         cout << bitset<10>(i) << nL;
    //     }
    // }
    int nc; cin >> nc;
    rep(cn, 0, nc){
        ll n; cin >> n;
        auto parity = [](ll x) -> int {
            return __builtin_popcountll(x) % 2;
        };
        ll a = 0, b = 0; 
        if(parity(n) == 1){
            cout << "second" << endl;
            cin >> a >> b;
            if(a == 0 && b == 0) continue;
        }
        else{
            cout << "first" << endl;
        }
        do {
            if(a) n = (parity(a) ? b : a);
            int bs = __builtin_popcountll(n);
            assert(bs % 2 == 0);
            ll y = 0;
            int times = bs/2;
            if(!(times & 1)) times--;
            rep(i, 0, times){
            // rep(i, 0, bs/2){
                ll x= n & -n;
                y ^= x;
                n ^= x;
            }
            // assert(parity(n) == 1 && parity(y) == 1);
            // assert()
            cout << y << " " << n << endl;
            cin >> a >> b;
        } while(!(a == 0 && b == 0));
    }
    
    return 0;
}
