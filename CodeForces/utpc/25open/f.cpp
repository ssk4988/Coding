#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vl = vector<ll>;

#define sz(x) (int)x.size()
#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)
const int D = 250;
using mat = array<array<ll, D>, D>;
mat zero() {
    mat res;
    rep(i, 0, D){
        rep(j, 0, D) res[i][j] = 0;
    }
    return res;
}
mat id() {
    mat res;
    rep(i, 0, D){
        rep(j, 0, D) res[i][j] = i==j;
    }
    return res;
}
const ll mod = 1e9+7;
mat operator*(mat &a, mat &b){
    mat res=zero();
    rep(i, 0, D){
        rep(j, 0, D){
            rep(k, 0, D) (res[i][j] += a[i][k] * b[k][j]) %= mod;
        }
    }
    return res;
}
mat matpow(mat a, ll p) {
    mat res=id();
    for(; p; a=a*a, p/=2) {
        if(p&1) res = res * a;
    }
    return res;
}
ll modpow(ll b, ll e) {
    ll res = 1;
    for(; e; b=(b*b)%mod, e /= 2){
        if(e&1) (res *= b) %= mod;
    }
    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m, k; cin >> n >> m >> k;
    vi outdeg(n);
    vector<array<int, 3>> ed(m);
    rep(i, 0, m){
        rep(j, 0, 3) cin >> ed[i][j];
        ed[i][0]--, ed[i][1]--;
        outdeg[ed[i][0]]++;
        outdeg[ed[i][1]]++;
    }
    mat a=zero();
    rep(i, 0, m) {
        auto [u, v, t] = ed[i];
        if(u != n-1) {
            (a[u][(t-1)*n+v] += modpow(outdeg[u], mod-2)) %= mod;
        }
        if(v != n-1) (a[v][(t-1)*n+u] += modpow(outdeg[v], mod-2)) %= mod;
    }
    rep(i, 0, n){
        if(outdeg[i] == 0 || i == n-1) {
            a[i][i]=1;
        }
    }
    rep(i, 0, n) {
        rep(t, 1, 5) {
            a[t*n+i][(t-1)*n+i]=1;
        }
    }
    mat res = matpow(a, k);
    cout << res[0][n-1] << "\n";
    return 0;
}
