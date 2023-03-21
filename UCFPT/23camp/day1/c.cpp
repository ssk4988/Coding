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
int MOD = 1'000'000'000 + 7;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    // check what happens for k == 0
    int p, k; cin >> p >> k;
    if(k == 0){
        ll ans = 1;
        rep(i, 0, p - 1){
            ans = (ans * p) % MOD;
        }
        cout << ans << nL;
        return 0;
    }
    vector<bool> cycled(p);
    vi next(p);
    vi cyclesize(p);
    vi cyclefreq(p + 1);
    rep(i, 0, p){
        ll i1 = i;
        i1 = (k * i1) % p;
        next[i] = int(i1);
    }
    vi firsts;
    rep(i, 0, p){
        if(cycled[i]) continue;
        firsts.pb(i);
        int cur = i;
        int len = 0;
        while(!cycled[cur]){
            cycled[cur] = true;
            len++;
            cur = next[cur];
        }
        cyclefreq[len]++;
        cyclesize[i] = len;
        cur = next[i];
        while(cur != i){
            cyclesize[cur] = len;
            cur = next[cur];
        }
    }
    rep(i, 0, sz(cyclefreq)){
        cyclefreq[i] = (cyclefreq[i] * i) % MOD;
    }
    vl cyclefreqsum(sz(cyclefreq));
    rep(i, 1, sz(cyclefreqsum)){
        for(int j = i; j < sz(cyclefreqsum); j += i){
            cyclefreqsum[j] = (cyclefreqsum[j] + cyclefreq[i]) % MOD;
        }
    }
    ll ans = 1;
    for(int i : firsts){
        ans = (ans * cyclefreqsum[cyclesize[i]]) % MOD;
    }
    cout << ans << nL;
    
    return 0;
}
