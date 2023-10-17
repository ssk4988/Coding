#include <bits/stdc++.h>
using namespace std;

#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)

using vi = vector<int>;
using ll = long long;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;
using vl = vector<ll>;

const ll MOD = 1e9 + 7;
ll mod(ll k){
    return k % MOD;
}
ll mod1(ll k){
    return (k % MOD + MOD) % MOD;
}
struct ModChoose {
    // const ll MOD;
    const int LIM;
    vl inv, fact, invfact;
    ModChoose(int n) : LIM(n + 1), inv(LIM), fact(LIM), invfact(LIM) {
        fact[0] = invfact[0] = inv[1] = fact[1] = invfact[1] = 1;
        rep(i, 2, LIM){
            inv[i] = MOD - (MOD / i) * inv[MOD % i] % MOD;
            fact[i] = (i * fact[i - 1]) % MOD;
            invfact[i] = (inv[i] * invfact[i - 1]) % MOD;
        }
    }
    ll choose(int n, int k){
        if(k > n || k < 0) return 0;
        return (fact[n] * invfact[k]) % MOD * invfact[n - k] % MOD;
    }
    ll starsbars(int numalloc, int numvars){
        return choose(numalloc + numvars - 1, numvars - 1);
    }
};
int n, h; 
// ModChoose c;
vi freq, pref;
ll ans = 0;
int aff;
vi assigned;
void bt(vi &perm, int used, int mx, vi &left){
    rep(i, 0, h){
        if(used == pref[i] && mx < pref[i]) return;
    }
    if(used == n){
        ans++;
        return;
    }
    rep(i, 0, n){
        if(left[i] == 0) continue;
        left[i]--;
        perm.push_back(i);
        bt(perm, used + 1, max(mx, i), left);
        perm.pop_back();
        left[i]++;
    }
}

int main(){
    // cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cin >> n >> h;
    // c = ModChoose(2 * n + 100);
    // assigned.resize(n);

    // if(h == 0){
    //     cout << c.fact[n] << "\n";
    //     return 0;
    // }
    freq = vi(h);
    // int cur = 0;
    rep(i, 0, h){
        cin >> freq[i];
        // rep(j, 0, freq[i]){
        //     assigned[cur++] = i;
        // }
    }
    sort(all(freq));
    reverse(all(freq));
    pref = vi(freq);
    rep(i, 1, h){
        pref[i] += pref[i - 1];
    }
    aff = pref.back();
    // if(n - pref.back() == 0){
    //     cout << 0 << "\n";
    //     return 0;
    // }
    vi perm; vi left(n, 1);
    bt(perm, 0, false, left);
    cout << ans << "\n";


    return 0;
}
