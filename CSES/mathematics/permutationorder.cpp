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

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    vl fact(22);
    fact[0] = 1;
    rep(i, 1, sz(fact)) fact[i] = fact[i-1] * i;
    rep(cn, 0, nc) {
        int t; cin >> t;
        if(t == 1) {
            ll n, k; cin >> n >> k;
            k--;
            vi left;
            rep(i, 0, n) left.pb(i);
            rep(i, 0, n) {
                int d = 0;
                while(k >= fact[n-1-i]) {
                    k -= fact[n-1-i];
                    d++;
                }
                cout << left[d]+1 << " ";
                left.erase(begin(left)+d);
            }
            cout << "\n";
        } else {
            int n; cin >> n;
            vi perm(n);
            vi left;
            rep(i, 0, n) {
                cin >> perm[i]; perm[i]--;
                left.pb(i);
            }
            ll k = 1;
            rep(i, 0, n) {
                auto it = find(all(left), perm[i]);
                int d = it - begin(left);
                k += d * fact[n-1-i];
                left.erase(it);
            }
            cout << k << "\n";
        }
    }
    
    return 0;
}
