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

const int LIM = 1e6 + 10;
vi pfs[LIM];
int mobius[LIM];
bool composite[LIM];
int freq[LIM];
vector<int> lp(LIM);
vector<int> pr;
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    mobius[1] = 1;
    for (int i=2; i < LIM; ++i) {
        if (lp[i] == 0) {
            lp[i] = i;
            pr.push_back(i);
            mobius[i] = -1;
        }
        else{
            int cur = i;
            mobius[i] = mobius[1];
            while(cur > 1){
                int rem = 1, p1 = lp[cur];
                int pp = 0;
                while(lp[cur] == p1){
                    rem *= p1;
                    cur /= p1;
                    pp++;
                }
                mobius[i] *= pp > 1 ? 0 : mobius[rem];
            }
        }
        for (int j = 0; i * pr[j] < LIM; ++j) {
            lp[i * pr[j]] = pr[j];
            if (pr[j] == lp[i]) {
                break;
            }
        }

    }
    rep(i, 0, LIM){
        pfs[i].pb(1);
    }


    composite[0] = composite[1] = true;
    vi primes;
    int n;
    cin >> n;
    vl a(n);
    unordered_set<int> stuff;
    rep(i, 0, n){
        cin >> a[i];
        stuff.insert(a[i]);
    }
    rep(i, 2, LIM){
        // pfs[i].pb(i);
        ll sq = ll(i) * i;
        if(sq >= LIM) break;
        for(int j = i * i; j < LIM; j += i){
            if(stuff.count(j)) 
                pfs[j].pb(i);
            if(!composite[i]){
                composite[j] = true;
            }
        }
    }
    ll ans = 0;
    // set<int> ss;
    rep(i, 0, n){
        for(int j : pfs[a[i]]){
            ans += freq[j] * mobius[j];
            freq[j]++;
            int other = a[i] / j;
            if(other > j){
                ans += freq[other] * mobius[other];
                freq[other]++;
            }
        }
    }
    cout << ans << nL;
    

    
    
    return 0;
}