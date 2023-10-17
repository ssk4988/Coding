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

ll MOD = 1e9 + 7;
ll mod(ll k) {
    return k % MOD;
}

ll modpow(ll b, ll p){
    if(p == 0) return 1;
    if(p == 1) return b;
    ll res = modpow(b, p/2);
    res = mod(res * res);
    if(p % 2 == 1) res = mod(res * b);
    return res;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    vl fib(200);
    fib[0] = fib[1] = 1;
    rep(i, 2, sz(fib)){
        fib[i] = mod(fib[i - 1] + fib[i - 2]);
        // cout << i << " " << fib[i] << nL;
    }
    srand(time(NULL));
    int lim = 98;
    unordered_map<ll, vi> mm;
    const int iterations = 1000000;
    // auto gen = [&](i)
    rep(i, 0, iterations){
        int cnt = 0;
        vi arr;
        ll mult = 1;
        while(cnt < lim){
            int cycle = (rand() % (lim - cnt)) + 1;
            cnt += (sz(arr) > 0) + cycle;
            arr.pb(cycle);
            mult = mod(mult * fib[cycle]);
        }
        mm[mult] = arr;
    }
    // cout << sz(mm) << nL;
    unordered_set<ll> ss;
    vl res;
    for(auto [key, val] : mm){
        res.pb(key);
        // for(auto [key1, val1] : mm){
        //     ss.insert(mod(key * key1));
        // }
    }
    // rep(i, 0, sz(res)){
    //     rep(j, 0, i + 1){
    //         ss.insert(mod(res[i] * res[j]));
    //     }
    // }
    // cout << sz(ss) << nL;
    ll n; cin >> n;
    if(n == 0){
        cout << "##.\n.##\n";
        return 0;
    }
    for(auto i : res){
        ll inv = modpow(i, MOD - 2);
        ll target = mod(n * inv);
        if(mm.count(target)){
            vvi grid(2, vi(200)); // 0 is blocked, 1 is empty
            int col = 0;
            vi s1 = mm[i], s2 = mm[target];
            for(int i : s1){
                rep(j, 0, i){
                    grid[0][col] = grid[1][col] = 1;
                    col++;
                }
                col++;
            }
            for(int i : s2){
                rep(j, 0, i){
                    grid[0][col] = grid[1][col] = 1;
                    col++;
                }
                col++;
            }
            rep(j, 0, 2){
                rep(i, 0, sz(grid[j])){
                    cout << (grid[j][i] ? '.' : '#');
                }
                cout << nL;
            }
            return 0;
        }
    }
    assert(false);
    return 0;
}
