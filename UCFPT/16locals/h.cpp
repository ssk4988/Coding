#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;
using ll = long long;
using vl = vector<ll>;

#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int)x.size()

const int LIM = 1e7+1;
vl primes;
int frq[LIM], lp[LIM+1];

vi ps, es;
ll ans;
void dfs(int i, int c) {
    ans += frq[c];
    // cerr << "dfs " << i << " " << c << endl;
    rep(j, i, sz(ps)) {
        int c1 = c;
        rep(p, 1, es[j]+1) {
            c1 *= ps[j];
            dfs(j+1, c1);
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    rep(i, 2, LIM+1) {
        if(lp[i] == 0) primes.push_back(lp[i] = i);
        for(int j = 0; j < sz(primes) && i * primes[j] <= LIM && primes[j] <= lp[i]; ++j)
            lp[i * primes[j]] = primes[j];
    }
    // rep(i, 1, LIM) {
    //     for(int j = i; j < LIM; j += i) {
    //         divs[j].push_back(i);
    //     }
    // }

    int nc; cin >> nc;
    rep(cn, 0, nc) {
        int n; cin >> n;

        vi a(n);
        rep(i, 0, n) {
            cin >> a[i];
            frq[a[i]]++;
        }
        ans = 0;
        for(int x : a) {
            if(x == 0) continue;
            int y = x;
            while(x > 1) {
                int p = lp[x];
                ps.push_back(p);
                es.push_back(0);
                while(x % p == 0) {
                    es.back()++;
                    x /= p;
                }
                // cerr << y << " " << x << " " << ps.back() << " " << es.back() << endl;
            }
            dfs(0, 1);
            ans -= frq[y];
            ps.clear();
            es.clear();
        }

        ans += frq[0] * ll(n-frq[0]);
        for(int x : a) frq[x]--;
        cout << "Test case #" << (cn+1) << ": " << ans << "\n\n";
    }
    // int best = 0;
    // rep(i, 0, LIM) best = max(best, sz(divs[i]));
    // cout << best << endl;
    // rep(cn, 0, nc) {
    //     cerr << "bruh\n" << sz(divs[nc]) << " " << lp[nc] << "\n";;
    // }

    return 0;
}
