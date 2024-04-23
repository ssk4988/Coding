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

const ll MOD = 998244353;
inline ll mod(ll k){
    return k % MOD;
}
inline ll modneg(ll k){
    return (k % MOD + MOD) % MOD;
}

vi operator*(vi a, vi b){
    int pw = __builtin_ctz(sz(a));
    assert(sz(a) == sz(b) && sz(a) == 1 << pw);
    for(int p = pw - 1; p >= 0; p--){
        for(int i = 0; i < sz(a); i += 1 << (p+1)){
            for(int j = 0; j < (1 << p); j++){
                a[i+j] = (a[i+j] + a[i+j+(1<<p)]) % MOD;
                a[i+j+(1<<p)] = (a[i+j] - 2 * a[i+j+(1<<p)]) % MOD;
                b[i+j] = (b[i+j] + b[i+j+(1<<p)]) % MOD;
                b[i+j+(1<<p)] = (b[i+j] - 2 * b[i+j+(1<<p)]) % MOD;
            }
        }
    }
    rep(i, 0, sz(a)) a[i] = (ll(a[i]) * b[i]) % MOD;
    rep(p, 0, pw){
        for(int i = 0; i < sz(a); i += 1 << (p+1)){
            for(int j = 0; j < (1 << p); j++){
                b[i+j] = ((a[i+j] + a[i+j+(1<<p)]) % MOD * ll(MOD+1)/2) % MOD;
                b[i+j+(1<<p)] = (a[i+j] - b[i+j]) % MOD;
            }
        }
        swap(a, b);
    }
    return a;
}


int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vi a(1 << n), b(1 << n);
    rep(i, 0, 1 << n){
        cin >> a[i];
    }
    rep(i, 0, 1 << n){
        cin >> b[i];
    }
    vi c = a * b;
    rep(i, 0, 1 << n){
        if(c[i] < 0) c[i] += MOD;
        cout << c[i] << " ";
    }
    cout << nL;
    
    return 0;
}
