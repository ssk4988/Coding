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

ll modpow(ll b, ll e) {
	ll ans = 1;
	for (; e; b = b * b % MOD, e /= 2)
		if (e & 1) ans = ans * b % MOD;
	return ans;
}
ll modinv(ll k){
    return modpow(k, MOD-2);
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n; ll k; cin >> n >> k;
        vl b(n+1);
        rep(i, 1, n+1) cin >> b[i];
        vl a(n+1, -1);
        vvi adj(n+1);
        rep(i, 1, n+1){
            // for(int c = i + (i & -i); c <= n; c += c & -c) adj[c].pb(i);
            int c = i + (i & -i);
            if(c <= n) adj[c].pb(i);
        }
        vl p(20);
        p[0] = 1; // k-1 c k-1
        rep(i, 1, sz(p)){
            p[i] = mod(mod(p[i-1] * (k - 1 + i)) * modinv(i));
        }
        // for(auto x : p){
        //     cout << x << " ";
        // }
        // cout << "\n";
        vector<vl> base(n+1, vl(20));
        auto solve = [&](int i, auto &&solve) -> void {
            if(a[i] != -1) return;
            if(i % 2 == 1){
                a[i] = b[i];
                base[i][0] = a[i];
                return;
            }
            for(int u : adj[i]){
                solve(u, solve);
                rep(j, 0, sz(base[u]) - 1){
                    base[i][j+1] = mod(base[i][j+1] + base[u][j]);
                }
            }
            a[i] = b[i];
            rep(j, 0, sz(base[i])){
                a[i] = mod(mod(a[i] - mod(p[j] * base[i][j])) + MOD);
            }
            base[i][0] = a[i];
        };
        rep(i, 1, n+1){
            solve(i, solve);
        }
        rep(i, 1, n+1){
            cout << a[i] << " ";
        }
        cout << "\n";
    }
    
    return 0;
}
