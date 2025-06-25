#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vii = vector<pii>;
using vll = vector<pll>;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

const ll mod = 998244353;
ll modpow(ll b, ll e) {
    ll res = 1;
    for(; e; (b *= b) %= mod, e /= 2)
        if(e&1) (res *= b) %= mod;
    return res;
}

struct UF {
    vi e;
    UF(int n) : e(n, -1) {}
    int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
    bool join(int a, int b) {
        a = find(a), b = find(b);
        if(a == b) return false;
        if(e[a] > e[b]) swap(a, b);
        e[a] += e[b]; e[b] = a;
        return true;
    }
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    int n; cin >> n;
    map<vi, ll> dp;
    auto go = [&](vi c, auto &&go) -> ll {
        if(sz(c) == 1) return 0;
        if(dp.count(c)) return dp[c];
        ll &ans = dp[c];
        int pairs = n * n;
        int reach = 0;
        rep(i, 0, sz(c)) {
            rep(j, 0, sz(c)) {
                if(i == j) continue;
                reach += c[i] * c[j];
                vi b(c);
                b[i] += b[j];
                b.erase(begin(b) + j);
                sort(all(b));
                (ans += c[i] * c[j] % mod * go(b, go)) %= mod;
            }
        }
        (ans *= modpow(reach, mod-2)) %= mod;
        (ans += pairs * modpow(reach, mod-2) % mod) %= mod;
        return ans;
    }; 
    rep(cn, 0, nc) {
        UF uf(n);
        int m; cin >> m;
        rep(i, 0, m) {
            int u, v; cin >> u >> v; u--, v--;
            uf.join(u, v);
        }
        vi c;
        rep(i, 0, n) {
            if(uf.find(i) == i) c.pb(-uf.e[i]);
        }
        sort(all(c));
        cout << go(c, go) << "\n";
    }
    
    return 0;
}
