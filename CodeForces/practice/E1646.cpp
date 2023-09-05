#include <bits/stdc++.h>
#include <bits/extc++.h>
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

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};



int main()
{
    // cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m; cin >> n >> m;
    vl res(21);
    ll ans = 1; // for n = 1
    // unordered_set<ll, custom_hash> ss;
    bitset<20000005> u;
    rep(i, 1, 21){
        for(ll j = i, cnt = 0; cnt < m; j += i, cnt++){
            // ss.insert(j);
            if(!u[j]) res[i]++;
            u[j] = true;
        }
        res[i] += res[i - 1];
        // cout << "precomped " << i << " " << res[i] << " " << (res[i] - res[i - 1]) << nL;
    }
    vi used(n + 1);
    for(ll i = 2; i <= n; i++){
        if(used[i]) continue;
        int p = 1;
        ll cur = i;
        used[cur] = true;
        while(cur * i <= n){
            cur *= i;
            used[cur] = true;
            p++;
        }
        ans += res[p];
    }
    cout << ans << nL;
    
    return 0;
}
