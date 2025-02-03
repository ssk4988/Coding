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

const ll LIM = 1e18;

ll mult(ll a, ll b) {
    if(a == 0) return a * b;
    ll maxb = LIM / a;
    return b <= maxb ? a * b : LIM;
}
ll add(ll a, ll b) { return min(a + b, LIM); }

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m; ll k; cin >> n >> m >> k;
    // cerr << "n=" << n << ", m=" << m << " k=" << k << endl;
    vector dp(n+1, vector(n+1, vector(n+1, -1LL)));
    vl fact(n+1);
    fact[0] = 1;
    rep(i, 1, n+1) fact[i] = mult(fact[i-1], i);
    auto go = [&](int pref, int fixedleft, int match, auto &&go) -> ll {
        if(match < 0 || fixedleft < 0) return 0;
        auto &ans = dp[pref][fixedleft][match];
        if(ans != -1) return ans;
        int blocked = n - pref - match;
        if(match == 0) {
            ans = fixedleft == 0 ? fact[blocked] : 0;
            // cerr << "no matches left: blocked-" << blocked << " dp: " << pref << " " << fixedleft << " " << match << " = " << ans << endl;
            return ans;
        }
        if(pref == n) {
            ans = (fixedleft == 0);
            // cerr << pref << " " << fixedleft << " " << match << " = " << ans << endl;
            return ans;
        }
        ans = 0;
        // fixed point
        ans = add(ans, go(pref+1, fixedleft-1, match-1, go));
        // use another match
        ans = add(ans, mult(go(pref+1, fixedleft, match-2, go), match-1));
        // use a blocked element
        ans = add(ans, mult(go(pref+1, fixedleft, match-1, go), blocked));
        // cerr << pref << " " << fixedleft << " " << match << " = " << ans << endl;
        return ans;
    };
    ll tot = go(0, m, n, go);
    if(tot < k){
        cout << "-1\n";
        // cerr << tot << endl;
        return 0;
    }
    vi used(n);
    vi perm;
    auto eval = [&]() -> pi {
        int match = n - sz(perm), fixedleft = m;
        rep(j, 0, sz(perm)) if(perm[j] == j) fixedleft--;
        rep(j, 0, sz(perm)) if(perm[j] >= sz(perm)) match--;
        return {match, fixedleft};
    };
    rep(i, 0, n) {
        int use = -1;
        {
            auto [match, fixedleft] = eval();
            // cerr << "state: " << i << " " << fixedleft << " " << match << " k: " << k << endl;
            // rep(j, 0, sz(perm)) cerr << perm[j] << " ";
            // cerr << endl;
        }
        rep(v, 0, n) {
            if(used[v]) continue;
            // if(match == 0) {
            //     ll nxt = fact[n-(i+1)];
            //     if(nxt >= k) {
            //         use = v;
            //         break;
            //     } else k -= nxt;
            // }
            perm.pb(v);
            used[v] = true;
            auto [match, fixedleft] = eval();
            ll nxt = go(i+1, fixedleft, match, go);
            if(nxt >= k) {
                use = v;
                break;
            }
            k -= nxt;
            used[v] = false;
            perm.pop_back();
            // if(v == i) {
            //     ll nxt = go(i+1, fixedleft-1, match-1, go);
            //     if(nxt >= k) {
            //         use = v;
            //         fixedleft--;
            //         match--;
            //         break;
            //     } else k -= nxt;
            // } else if(v < i) {
            //     // use blocked

            //     ll nxt = go(i+1, fixedleft, match-1, go);
            //     if(nxt >= k) {
            //         match--;
            //         use = v;
            //         break;
            //     } else k -= nxt;
            // } else {
            //     // use match
            //     ll nxt = go(i+1, fixedleft, match-2, go);
            //     if(nxt >= k) {
            //         match -= 2;
            //         use = v;
            //         break;
            //     } else k -= nxt;
            // }
        }
        // cerr << "add " << use << endl;
        assert(use != -1);
    }
    rep(i,0,n){
        cout << perm[i]+1 << " ";
    }
    cout << "\n";
    
    return 0;
}
