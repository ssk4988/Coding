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

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    const int LIM = 1e6 + 100;
    // vvi fs(LIM);
    vi lp(LIM+1), primes;
    rep(i, 2, LIM+1) {
        if (lp[i] == 0) primes.push_back(lp[i] = i);
        for (int j = 0; j < sz(primes) &&  i * primes[j] <= LIM && primes[j] <= lp[i]; ++j) 
            lp[i * primes[j]] = primes[j];
    }
    // rep(i, 2, LIM){
    //     if(sz(fs[i]) == 0){
    //         for(int j = i; j < LIM; j += i){
    //             fs[j].pb(i);
    //         }
    //     }
    // }
    auto addpf = [&](map<int, int>& freq, ll &d, int x)->void{
        int x1 = x;
        while(x1 > 1){
            int p = lp[x1];
            d /= (freq[p] + 1);
            freq[p]++;
            d *= (freq[p] + 1);
            x1 /= p;
        }
        // for(int j : fs[x]){
        //     d /= (freq[j] + 1);
        //     freq[j]++;
        //     d *= (freq[j] + 1);
        // }
    };
    rep(cn, 0, nc){
        int n, q; cin >> n >> q;
        map<int, int> freq0, freq;
        ll d0 = 1;
        ll d = 1;
        addpf(freq0, d0, n);
        d = d0;
        freq = map<int, int>(freq0);
        ll n1 = n;
        rep(i, 0, q){
            int t; cin >> t;
            if(t == 2){
                n1 = n;
                d = d0;
                freq = map<int, int>(freq0);
            }
            else{
                int x; cin >> x;
                addpf(freq, d, x);
                n1 *= x;
                bool works = true;
                ll n2 = d;
                for(auto [p, e] : freq){
                    int e1 = 0;
                    while(n2 % p == 0){
                        n2 /= p;
                        e1++;
                    }
                    if(e1 > e) works = false;
                }
                cout << (works && n2 == 1 ? "YES" : "NO") << nL;
            }
        }
    }
    
    return 0;
}
