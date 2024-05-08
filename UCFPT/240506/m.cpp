#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ll = long long;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;
using vl = vector<ll>;

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)

const ll mod = 998244353;
ll modpow(ll b, ll e) {
    ll ans = 1;
    for(; e; b = b * b % mod, e /= 2){
        if(e & 1) ans = ans * b % mod;
    }
    return ans;
}
inline ll modinv(ll k) {
    return modpow(k, mod-2);
}
using a2 = array<ll, 2>;
int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    // adj is adjacency list
    vvi adj;
    // is the leaf node special
    vi special;
    // case out no internal nodes
    auto go = [&](int u, int p, auto &&go) -> a2 {
        int childcount = 0;
        a2 res = {1, 0};
        vector<a2> child;
        for(int v : adj[u]) if(v != p) {
            childcount++;
            a2 c = go(v, u, go);
            (res[0] *= (c[0] + c[1])) %= mod;
            child.push_back(c);
        }
        for(a2 c : child){
            (res[1] += res[0] * c[1] % mod * modinv(c[0] + c[1])) %= mod;
        }
        if(childcount == 0){
            res = {0, 0};
            res[special[u]] = 1;
        }
        return res;
    };

    return 0;
}
