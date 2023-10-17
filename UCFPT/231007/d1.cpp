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
    while(sz(str) < n){
        str.push_back(str[sz(str) % k]);
    }
    ll lower = k, higher = n - (k - 1);
    k = n;
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
    set<ll> strs;
    int cnt = 0;
    rep(len, 1, k + 1){
        int cont = 0, tot = 0;;
        rep(j, 0, k){
            if(j + len - 1 >= sz(str)) continue;
            if(!strs.count(hsh(j, j + len - 1))) cont++;
            tot++;
            strs.insert(hsh(j, j + len - 1));
            // cout << i << " " << j << " " << hsh(i, j) << nL;
            cnt++;
        }
        if(len < lower || len > higher) cout << len << " " << cont << nL;
    }
    cout << sz(strs) << nL;
    cout << str << nL;
    return 0;
}
