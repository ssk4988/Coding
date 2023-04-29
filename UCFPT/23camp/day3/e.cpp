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


int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int LIM = 5e5 + 10;
    vvi pfs(LIM, {1});
    vi mobius(LIM, 1);
    vi composite(LIM);
    composite[0] = composite[1] = true;
    vi primes;
    rep(i, 2, LIM){
        pfs[i].pb(i);
        if(!composite[i]){
            primes.pb(i);
            mobius[i] = -1;
        } 
        ll sq = ll(i) * i;
        for(int j = i * 2; j < LIM; j += i){
            pfs[j].pb(i);
            if(!composite[i]){
                composite[j] = true;
                if(j % sq == 0) mobius[j] = 0;
                else mobius[j] *= mobius[i];
            }
        }
    }
    int n, q;
    cin >> n >> q;
    vl a(n);
    rep(i, 0, n){
        cin >> a[i];
    }
    vi freq(LIM);
    ll ans = 0;
    set<int> ss;
    rep(i, 0, q){
        int v; cin >> v;v--;
        if(ss.find(v) != ss.end()){
            ss.erase(v);
            for(int j : pfs[a[v]]){
                freq[j]--;
                ans -= freq[j] * mobius[j];
            }
        }
        else{
            ss.insert(v);
            for(int j : pfs[a[v]]){
                ans += freq[j] * mobius[j];
                freq[j]++;
            }
        }
        cout << ans << nL;
    }
    

    
    
    return 0;
}