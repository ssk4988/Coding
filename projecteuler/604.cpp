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
    ll n; cin >> n;
    n++;
    const int lim = 5e6;
    vl phi(lim);
    rep(i,0,lim) phi[i] = i&1 ? i : i/2;
	for (int i = 3; i < lim; i += 2) if(phi[i] == i)
		for (int j = i; j < lim; j += i) phi[j] -= phi[j] / i;
    // ll tot = 0;
    // rep(i, 0, 50) {
    //     tot += phi[i]*i;
    //     cout << i << " " << phi[i] << " " << tot << endl;
    // }
    ll tot = 0, terms = 0;

    rep(i, 2, lim) {
        ll amt = min((1+phi[i])/2, (n-tot)/i);
        terms += 2 * amt;
        tot += i * amt;
        // cerr << i << " " << amt << " " << phi[i] << " " << tot << " " << terms << endl;
        if(amt == 0) {
            cerr << "done" << endl;
            break;
        }
    }
    cout << terms << "\n";
    return 0;
}
