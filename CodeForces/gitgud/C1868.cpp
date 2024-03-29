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

const ll MOD = 998244353;
inline ll mod(ll k) {
    return k % MOD;
}
inline ll mod1(ll k){
    return (k % MOD + MOD) % MOD;
}

ll modpow(ll b, ll e) {
	ll ans = 1;
	for (; e; b = b * b % MOD, e /= 2)
		if (e & 1) ans = ans * b % MOD;
	return ans;
}

const int L = 130;
vvl root(vvl &a, vvl &b){
    vvl res(L, vl(2)); // 0 all paths, 1 can extend with root
    // a[0] = mod(a[0] + 1);
    // b[0] = mod(b[0] + 1);

    rep(i, 1, L){
        rep(j, 1, L){
            if(i + j + 1 >= L) continue;
            res[i + j + 1][0] = mod(a[i][1] * b[j][1] + res[i + j + 1][0]);
        }
    }
    res[1][1] = mod(res[1][1] + 1);
    rep(i, 2, L){
        res[i][1] = mod(res[i][1] + a[i-1][1] + b[i-1][1]);
    }
    rep(i, 0, L){
        res[i][0] = mod(res[i][0] + res[i][1] + a[i][0] + b[i][0]);
    }
    return res;
}

// vvl operator+(vvl &a, vvl &b) {
//     vvl res(L, vl(2));
//     rep(i, 0, L) res[i] = mod(a[i] + b[i]);
//     return res;
// }

const int MAX_M = 1e5 + 10;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    vector<vl> pw(MAX_M, vl(L));
    rep(i, 0, MAX_M){
        pw[i][0] = 1;
        rep(j, 1, L){
            pw[i][j] = mod(pw[i][j-1] * i);
        }
    }
    // cout << "got here" << endl;
    vector<vvl> complete(L, vvl(L, vl(2))); // path lengths where node depth is [i]
    // complete[0][0][0] = complete[0][0][1] = 1;
    rep(i, 1, L){
        complete[i] = root(complete[i-1], complete[i-1]);
    }
    // rep(i, 0, 3){
    //     cout << "complete " << i << endl;
    //     rep(j, 0, 10) cout << j << " " << complete[i][j][0] << endl;
    // }
    // cout << "got here" << endl;
    int nc; cin >> nc;
    rep(cn, 0, nc){
        ll n; int m; cin >> n >> m;
        vl e(L);
        rep(i, 1, L){
            // e[i] = e[i-1];
            rep(x, 1, m+1){
                e[i] = mod(e[i] + mod(x * mod1(pw[x][i] - pw[x-1][i])));
            }
        }
        // rep(i, 0, 6){
        //     cout << i << " " << e[i] << endl;
        // }
        auto dfs = [&](ll u, auto &&dfs) -> vvl {
            ll l = u, r = u+1;
            int cnt = 0;
            while(r - 1 <= n){
                l = l * 2, r = r * 2;
                cnt++;
            }
            if(l > n){
                // complete cover
                // cout << "on " << u << " using complete node depth " << (sz(ls) - 1) << endl;
                return complete[cnt];
            }
            vvl lef = dfs(u * 2, dfs), rig = dfs(u * 2 + 1, dfs);
            return root(lef, rig);
        };
        vvl pathcnt = dfs(1, dfs);
        // cout << "Pathcnt: " << endl;
        // rep(i, 0, 11){
        //     cout << i << " " << pathcnt[i][0] << endl;
        // }
        ll ans = 0;
        rep(i, 0, L){
            ans = mod(ans + mod(pathcnt[i][0] * mod(e[i] * modpow(m, n - i))));
        }
        cout << ans << "\n";
    }
    
    return 0;
}
