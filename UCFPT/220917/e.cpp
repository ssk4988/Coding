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
int m = 100007;

ll mod(ll k){
    return k % m;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    n--;
    ll fib[2*n+10];
    fib[0] = 0;
    fib[1] = 1;
    //ll preffib[n];
    
    rep(i, 2, 2*n+10){
        fib[i] = mod(fib[i-1] + fib[i-2]);
    }
    //preffib[0] = 1;
    /*rep(i, 1, n){
        preffib[i] = mod(preffib[i-1] + fib[2*i + 1]);
        //cout << preffib[i] << " " << i << nL;
    }*/
    ll ans = 0;
    rep(i, 0, n-1){
        ans = mod(ans + mod(fib[2 * i + 1] * fib[2 * (n - i - 1)]));
        //cout << fib[2 * i + 1] << " " << fib[2 * (n - i - 1)] << nL;
    }
    /*rep(i, 1, n){
        
        rep(j, 0, i){
            //cout << fib[2*j+1] << " " << fib[2*(i-1-j)+1] << " " << fib[2 * j+1] * fib[2 * (i-1-j)+1] << nL;
            ans = mod(ans + mod(fib[2 * j+1] * fib[2 * (i-1-j)+1]));
        }
    }*/
    cout << ans << nL;
    
    return 0;
}