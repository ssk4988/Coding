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

ll MOD = 1e9 +7;

ll mod(ll k){
    return (k % MOD + MOD) % MOD;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, k; cin >> n >> k;
    vvi adj(n);
    rep(i, 0, n - 1){
        int a, b; cin >> a >> b;
        a--,b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    int LIM = 200'010;
    vl fact(LIM), invfact(LIM), inv(LIM);
    fact[0] = invfact[0] = inv[0] = 1;
    inv[1] = fact[1] = invfact[1] = 1;
    
    rep(i, 2, LIM){
        inv[i] = MOD - (MOD / i) * inv[MOD % i] % MOD;
        fact[i] = mod(fact[i - 1] * i);
        invfact[i] = mod(invfact[i - 1] * inv[i]);
        // assert(mod(fact[i] * invfact[i]) == 1);
    }
    auto choose = [&](int n, int k)->ll{
        if(k < 0 || k > n) return 0;
        return mod(mod(fact[n] * invfact[n - k]) * invfact[k]);
    };
    vi par(n), subsz(n);
    vvi adjsz(n);
    auto dfs = [&](int cur, int pre, auto&&dfs)->void{
        par[cur] = pre;
        subsz[cur]++;
        for(int nex : adj[cur]){
            if(nex == pre) continue;
            dfs(nex, cur, dfs);
            subsz[cur] += subsz[nex];
            adjsz[cur].pb(subsz[nex]);
        }
    };
    dfs(0, -1, dfs);
    rep(i, 0, n){
        // adjsz[i].pb(0); // verify this
        if(par[i] < 0 || par[i] >= n) continue;
        adjsz[i].pb(n - subsz[i]);
    }
    ll ans = 0;
    vl contrib(n);
    rep(i, 0, n){
        ll b = 0;
        for(int j : adjsz[i]){
            b = mod(b + choose(j, k));
        }
        for(int j : adjsz[i]){
            contrib[i] = mod(contrib[i] + 
                mod(mod(j * (n - j)) * 
                    mod(choose(n - 1 - j, k - 1) + 
                        mod(choose(n - 1 - j, k) + 
                            mod(-b + choose(j, k))
                        )
                    )
                )
            );
        }
        contrib[i] = mod(contrib[i] + 
            mod(n * 
                mod(choose(n - 1, k - 1) + 
                    mod(choose(n - 1, k) - b)
                )
            )
        );
        ans = mod(ans + contrib[i]);
    }
    cout << ans << nL;

    
    return 0;
}