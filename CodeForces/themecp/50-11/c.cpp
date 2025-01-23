#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vii = vector<pii>;
using vll = vector<pll>;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

const int LIM = 10005000;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    vi lp(LIM+1), primes;
    lp[1] = 1;
    rep(i, 2, LIM + 1) {
        if (lp[i] == 0) primes.push_back(lp[i] = i);
        for (int j = 0; j < sz(primes) && i * primes[j] <= LIM && primes[j] <= lp[i]; ++j) 
            lp[i * primes[j]] = primes[j];
    }
    vi pid(LIM+1);
    pid[1] = 1;
    rep(i, 1, sz(primes)) {
        pid[primes[i]] = i+1;
    }
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        int n; cin >> n;
        int sum = 0;
        rep(i, 0, n) {
            int a; cin >> a;
            sum ^= pid[lp[a]];
            // cout << a << " " << lp[a] << " " << pid[lp[a]] << "\n";
        }
        cout << (sum ? "Alice" : "Bob") << "\n";
    }
    
    return 0;
}
