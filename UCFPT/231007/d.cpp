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
ll mod(ll k ){
    return k % MOD;
}

ll mod1(ll k){
    return (k % MOD + MOD) % MOD;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    string str; cin >> str;
    int n; cin >> n;
    int k =sz(str);
    bool easy = false;
    if(n <= 3 * k){
        easy = true;
        while(sz(str) < n){
            str.push_back(str[sz(str) % k]);
        }
        k = n;
    }
    vl prefs;
    vl pows;
    pows.pb(1);
    const ll base = 29;
    rep(i, 0, k + 5){
        pows.pb(mod(base * pows.back()));
    }
    rep(i, 0, k){
        prefs.pb(mod((str[i] - 'a' + 1) * pows[i]));
        if(i > 0) prefs[i] = mod(prefs[i] + prefs[i - 1]);
    }
    auto hsh = [&](int l, int r)-> ll {
        ll ans = prefs[r];
        if(l) ans = mod1(ans - prefs[l-1]);
        ans = mod(ans * pows[k - l]);
        return ans;
    };
    if(easy){
        set<ll> strs;
        int cnt = 0;
        rep(i, 0, k){
            rep(j, i, k){
                strs.insert(hsh(i, j));
                // cout << i << " " << j << " " << hsh(i, j) << nL;
                cnt++;
            }
        }
        cout << sz(strs) << nL;
        // cout << "easy case! " << cnt << " " << str << k << "\n";
        return 0;
    }
    while(sz(str) < 3 * k + (n % k)){
        pows.pb(mod(pows.back() * base));
        str.push_back(str[sz(str) % k]);
        prefs.pb(mod(mod((str.back() - 'a' + 1) * pows[sz(str) - 1]) + prefs.back()));
    }
    unordered_set<ll> strs;
    rep(len, 1, k){
        ll cont = 0;
        rep(i, 0, k){
            if(!strs.count(hsh(i, i + len - 1))) cont++;
            strs.insert(hsh(i, i + len - 1));
            // assert(i + len - 1 < sz(prefs));
        }
        // cout << len << " " << cont << nL;
    }
    unordered_set<ll> rots;
    rep(i, 0, k){
        // assert(i + k - 1 < sz(prefs));
        rots.insert(hsh(i, i + k - 1));
    }
    ll lower = k, higher = n - (k - 1);
    assert(sz(prefs) == sz(str));
    rep(len, sz(str) - k + 2, sz(str) + 1){
        ll cont = 0, tot = 0;
        rep(i, 0, n){
            if(i + len - 1 >= sz(str)) break;
            // if(!strs.count(hsh(i, i + len - 1))) cont++;
            // else cout << "contained " << i << " " << (i + len - 1) << nL;
            tot++;
            // assert(i + len - 1 < sz(prefs));
            strs.insert(hsh(i, i + len - 1));
        }
        // cout << (n - sz(str) + len) << " " << cont << " " << tot << "\n";
    }
    ll ans = sz(strs) + sz(rots) * (higher - lower + 1);
    cout << ans << nL;
    // cout << str << nL;
    // cout << higher << " " << lower << " " << sz(rots) << " " << sz(strs) << nL;

    return 0;
}
