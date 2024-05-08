#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

// #pragma GCC optimize("Ofast")
using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;



const int LIM = 1000100;

int main() {
    cin.tie(0) -> sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    vi lp(LIM+1), primes;
    rep(i, 2, LIM+1) {
        if(lp[i] == 0) primes.push_back(lp[i] = i);
        for(int j = 0; j < sz(primes) && i * primes[j] <= LIM && primes[j] <= lp[i]; ++j)
            lp[i * primes[j]] = primes[j];
    }
    vvi pfs(LIM);
    vi lbl(LIM);
    int pre = 1;
    int best = 0;
    rep(i, 1, LIM){
        int cur = i;
        while(cur > 1){
            int p = lp[cur];
            if(sz(pfs[i]) == 0 || pfs[i].back() != p) pfs[i].push_back(p);
            cur /= p;
        }
        if(sz(pfs[i]) <= 1){
            pre = i;
        }
        else{
            
        }
        lbl[i] = 1;
        for(int p : pfs[i]) lbl[i] *= p;
    }
    
    

    return 0;
}
