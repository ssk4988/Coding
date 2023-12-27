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
#define bitat(x, b) (((x) >> (b)) & 1)

using mat = vector<vl>;
const ll M = 1e9 + 7;
inline ll mod(ll k){
    return k % M;
}

mat operator*(mat &a, mat &b){
    mat res(sz(a), vl(sz(b[0])));
    rep(i, 0, sz(res))
        rep(j, 0, sz(res[i]))
            rep(k, 0, sz(a[i]))
                res[i][j] = mod(mod(a[i][k] * b[k][j]) + res[i][j]);
    return res;
}

mat operator^(mat &b, ll p){
    if(p == 1) return b;
    mat res = b ^ (p/2);
    res = res * res;
    if(p & 1) res = res * b;
    return res;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, k; cin >> n >> k;
    string str; cin >> str;
    vector<mat> btrans(2, mat(1 << n, vl(1 << n)));
    rep(b, 0, 2){
        rep(pref, 0, sz(btrans[b])){
            rep(m, 0, sz(btrans[b])){
                if(__builtin_parity(m)) continue;
                int mask = m | (b << n);
                int bad = (~pref) & mask & (~(mask >> 1)) & ((1 << n) - 1);
                int pref2 = pref | ((~mask) & (mask >> 1));
                if(!bad) btrans[b][pref][pref2]++;
            }
        }
    }
    mat pat(btrans[str[0] - '0']);
    rep(i, 1, sz(str)) pat = pat * btrans[str[i] - '0'];
    mat res = pat ^ k;
    cout << res[0].back() << "\n";
    return 0;
}
