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

ll m = 1e9 + 7;

ll mod(ll k){
    return (k % m + m) % m;
}

ll modpow(ll k, ll b){
    if(b == 0) return 1;
    if(b == 1) return k;
    ll res = modpow(k, b / 2);
    res = mod(res * res);
    res = mod(res * modpow(k, b % 2));
    return res;
}

ll modinv(ll k){
    return modpow(k, m - 2);
}


vl fact;

ll modchoose(int n, int k){
    return mod(fact[n] * mod(modinv(fact[k]) * modinv(fact[n - k])));
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    fact.resize(1'200'000);
    fact[0] = fact[1] = 1;
    rep(i, 2, sz(fact)){
        fact[i] = mod(fact[i - 1] * i);
    }
    int n; cin >> n;
    vi a(n);
    rep(i, 0, n){
        cin >> a[i];
        a[i] /= 2;
    }
    ll ans = 1;//check n == 1
    rep(i, 1, n){
        if(a[i] > a[i - 1]){
            int numvar = a[i - 1] - 1;
            int numdiff = a[i] - a[i - 1];
            ans = mod(ans * modchoose(numvar +  numdiff, numvar));
        }
        else{
            ans = mod(ans * modchoose(a[i - 1], a[i]));
        }
    }
    cout << ans << nL;
    
    return 0;
}
