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

vl operator+(vl &a, vl &b){
    vl res(sz(a));
    rep(i, 0, sz(a)) res[i] = mod(a[i] + b[i]);
    return res;
}
vl operator-(vl &a, vl &b){
    vl res(sz(a));
    rep(i, 0, sz(a)) res[i] = modneg(a[i] - b[i]);
    return res;
}

vl operator*(vl a, vl b){
    if(sz(a) == 1) return {mod(a[0] * b[0])};
    vl a0(a.begin(), a.begin() + sz(a) / 2), a1(a.begin() + sz(a) / 2, a.end());
    vl b0(b.begin(), b.begin() + sz(b) / 2), b1(b.begin() + sz(b) / 2, b.end());
    vl d = (a0 + a1) * (b0 + b1);
    vl e = (a0 - a1) * (b0 - b1);
    vl c0 = d + e;
    rep(i, 0, sz(c0)) c0[i] = mod(c0[i] * (MOD+1)/2);
    vl c1 = d - c0;
    c0.insert(c0.end(), all(c1));
    return c0;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vl a(1 << n), b(1 << n);
    rep(i, 0, 1 << n){
        cin >> a[i];
    }
    rep(i, 0, 1 << n){
        cin >> b[i];
    }
    vl c = a * b;
    rep(i, 0, 1 << n){
        cout << c[i] << " ";
    }
    cout << nL;
    
    return 0;
}
