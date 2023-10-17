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

int myrandom (int i) { return std::rand()%i;}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    vi primes;
    rep(i, 2, 1001){
        bool works = true;
        rep(j, 2, i){
            if(i % j == 0){
                works = false;
                break;
            }
        }
        if(works){
            primes.pb(i);
            // cout << i << nL;
        }
    }
    // cout << primes.size() << nL;
    vl best1(300), best2(300);
    ll lim = 1e18;

    int iterations = 1000000;
    rep(iter, 0, iterations){
        vl sols;
        random_shuffle(all(primes), myrandom);
        for(int i : primes){
            bool used = false;
            // random_shuffle(all(sols), myrandom);
            rep(j, 0, sz(sols)){
                if(lim / sols[j] >= i){
                    sols[j] *= i;
                    used = true;
                    break;
                }
            }
            if(!used) sols.pb(i);
        }
        // cout << sz(sols) << nL;
        vl sols2;
        for(int i : primes){
            int ps = 0, v = 1;
            while(v * i <= 1000){ ps++, v *= i; }
            bool used = false;
            // random_shuffle(all(sols2), myrandom);
            rep(j, 0, sz(sols2)){
                if(lim / sols2[j] >= v){
                    sols2[j] *= v;
                    used = true;
                    break;
                }
            }
            if(!used) sols2.pb(v);
        }
        if(sz(sols) < sz(best1)) best1 = sols;
        if(sz(sols2) < sz(best2)) best2 = sols2;
    }

    cout << sz(best1) << nL;
    cout << sz(best2) << nL;

    // for(ll i : sols) cout << i << nL;
    rep(i, 1, 1001){
        int queries = 0;
        ll ans = 1;
        for(ll j : best2){
            ans *= __gcd(j, ll(i));
        }
        assert(ans == i);
    }


    return 0;
}
