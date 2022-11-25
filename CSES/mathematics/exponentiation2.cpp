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


ll mod(ll k, ll m){
    return k % m;
}

ll modpow(ll b, ll p, ll m){
    if(p == 0) return 1;
    if(p == 1) return b;
    ll a = modpow(b, p / 2, m);
    return mod(mod(a * a, m) * modpow(b, p % 2, m), m);
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; 
    cin >> n;
    ll m = 1000000007;
    rep(i, 0, n){
        int a, b, c;
        cin >> a >> b >> c;
        ll p = modpow(b, c, m - 1);
        cout << modpow(a, p, m) << nL;
    }
    
    return 0;
}