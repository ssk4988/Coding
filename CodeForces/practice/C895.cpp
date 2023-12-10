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

template<int B>
struct XORBasis {
	bitset<B> basis[B];
	int npivot = 0, nfree = 0;
	bool check(bitset<B> &v) {
		rep(i, 0, B)
			if (v.test(i)) v ^= basis[i];
		return v.none();
	}
	bool add(bitset<B> &v) {
		rep(i, 0, B)
			if (v.test(i)) {
				if (basis[i].none()) return basis[i] = v, ++npivot;
				v ^= basis[i];
			}
        return !++nfree;
	}
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    vi primes;
    for(int i = 2; i <= 70; i++){
        bool div = false;
        for(int j = 2; j < i; j++) if(i % j == 0) div = true;
        if(!div) primes.pb(i);
    }
    // cout << sz(primes) << nL;
    // 19 primes
    int n; cin >> n;
    XORBasis<19> x;
    rep(i, 0, n){
        int a; cin >> a;
        bitset<19> v;
        rep(j, 0, 19){
            while(a % primes[j] == 0){
                v[j].flip();
                a /= primes[j];
            }
        }
        // bool c = x.check(v);
        // assert(c != x.add(v));
        x.add(v);
    }
    const ll MOD = 1e9 + 7;
    ll ans = 1;
    rep(i, 0, x.nfree) ans = (ans * 2) % MOD;
    ans--;
    if(ans < 0) ans += MOD;
    cout << ans << nL;
    // cout << x.npivot << " " << x.nfree << nL;
    
    return 0;
}
