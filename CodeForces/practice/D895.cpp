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


const ll MOD = 1e9 + 7;
inline ll mod(ll k){
    return k % MOD;
}
int LIM = 1e6 + 10;
vl fact, inv, invfact;

// number perms greater than or equal to a
ll solve(string &a, vi &freq, int dig, bool match, bool canequal){
    if(!match){
        ll ans = fact[accumulate(all(freq), 0)];
        rep(i, 0, sz(freq)) ans = mod(ans * invfact[freq[i]]);
        return ans;
    }
    if(dig == sz(a)){
        return canequal;
    }
    ll ans = 0;
    rep(i, a[dig] - 'a' + 1, 26){
        if(freq[i] == 0) continue;
        freq[i]--;
        ans = mod(ans + solve(a, freq, dig+1, false, canequal));
        freq[i]++;
    }
    if(freq[a[dig] - 'a'] > 0) {
        freq[a[dig] - 'a']--;
        ans = mod(ans + solve(a, freq, dig+1, true, canequal));
        freq[a[dig] - 'a']++;
    }
    return ans;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    fact = vl(2, 1);
    inv = fact;
    invfact = fact;
    rep(i, 2, LIM) {
        fact.pb(mod(fact.back() * i));
        inv.pb(MOD - (MOD / i) * inv[MOD % i] % MOD);
        invfact.pb((inv[i] * invfact[i - 1]) % MOD);
    }
    string a, b; cin >> a >> b;
    vi freqa(26), freqb(26);
    for(char c : a) freqa[c - 'a']++;
    for(char c : b) freqb[c - 'a']++;
    ll ans = solve(a, freqa, 0, true, false);
    ll sub = solve(b, freqa, 0, true, true);
    ans = mod(ans - sub + MOD);
    cout << ans << "\n";
    
    return 0;
}