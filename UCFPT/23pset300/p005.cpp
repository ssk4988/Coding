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
using vvl = vector<vl>;

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

ll MOD;
vl pows;
ll mod(ll k){
    return (k % MOD + MOD) % MOD;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, q; cin >> n >> MOD >> q;
    string modstr = to_string(MOD);
    vvi adj(n);
    pows.pb(1);
    int bits = 21;
    rep(i, 0, 1 << (bits + 1)) pows.pb(mod(10 * pows.back()));
    rep(i, 0, n - 1){
        int a, b; cin >> a >> b; a--,b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    vl arr(n); 
    vi par(n), dep(n);
    rep(i, 0, n) cin >> arr[i];
    rep(i, 0, n) arr[i] = mod(arr[i]);
    auto dfs = [&](int cur, int p, int d, auto &&dfs)->void{
        par[cur] = p;
        dep[cur] = d;
        for(int i : adj[cur]){
            if(i == p) continue;
            dfs(i, cur, d + 1, dfs);
        }
    };
    dfs(0, 0, 0, dfs);
    vector<vvl> jmp(bits, vector<vl>(n, vl(3))); // {to, bottom-top inc sig, top-bottom inc sig}
    rep(i, 0, n){
        jmp[0][i] = {par[i], arr[i], arr[i]};
    }
    rep(i, 1, bits){
        rep(j, 0, n){
            vl mid = jmp[i-1][j];
            vl mid2 = jmp[i-1][mid[0]];
            jmp[i][j] = {mid2[0], 
            mod(mod(mid2[1] * pows[1 << (i-1)])+mid[1]), 
            mod(mod(mid[2] * pows[1 << (i-1)])+mid2[2])};
        }
    }
    auto lc = [&](int a, int b)->int{
        for(int i = bits-1; i >= 0; i--){
            if(dep[a] - (1 << i) >= dep[b]) a = jmp[i][a][0];
        }
        for(int i = bits-1; i >= 0; i--){
            if(dep[b] - (1 << i) >= dep[a]) b = jmp[i][b][0];
        }
        if(a == b) return a;
        for(int i = bits-1; i >= 0; i--){
            if(jmp[i][a][0] != jmp[i][b][0]){
                a = jmp[i][a][0], b = jmp[i][b][0];
            }
        }
        return jmp[0][a][0];
    };
    rep(i, 0, q){
        int a, b; cin >> a >> b;
        a--,b--;
        int l = lc(a, b);
        ll totlen = 0;
        ll ans = 0, curlen = 0;
        int d = dep[a] - dep[l];
        int cur = a;
        for(int i = bits-1; i >= 0; i--){
            if(d & (1 << i)){
                ans = mod(ans * pows[1 << i]);
                totlen += 1 << i;
                ans = mod(ans + jmp[i][cur][2]);
                cur = jmp[i][cur][0];
            }
        }
        ans = mod(ans * pows[1]);
        totlen++;
        ans = mod(ans + arr[l]);
        cur = b;
        d = dep[b] - dep[l];
        ll ans1 = 0;
        for(int i = bits-1; i >= 0; i--){
            if(d & (1 << i)){
                ans1 = mod(ans1 + mod(jmp[i][cur][1] * pows[curlen]));
                curlen += 1 << i;
                cur = jmp[i][cur][0];
            }
        }
        totlen += curlen;
        ans = mod(ans * pows[curlen]);
        ans = mod(ans + ans1);
        // string str = to_string(str);
        // while()
        cout << ans << "\n";
    }
    
    return 0;
}
