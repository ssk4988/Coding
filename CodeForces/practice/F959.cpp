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

template<int BITS = 32>
struct XORBasis {
	int basis[BITS] = {};
	int npivot = 0, nfree = 0;
	bool indep(int v) {
		for(int i = BITS - 1; i >= 0; i--)
			if (v & (1 << i)) v ^= basis[i];
		return v;
	}
	void add(int v) {
		for(int i = BITS - 1; i >= 0; i--)
			if (v & (1 << i)) {
				if (basis[i]) v ^= basis[i];
				else {
                    basis[i] = v;
                    npivot++;
                    return;
                }
			}
		nfree++;
	}
};

const ll mod = 1000000007; // faster if const

ll modpow(ll b, ll e) {
	ll ans = 1;
	for (; e; b = b * b % mod, e /= 2)
		if (e & 1) ans = ans * b % mod;
	return ans;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, q; cin >> n >> q;
    XORBasis<20> v;
    vi a(n);
    rep(i, 0, n){
        cin >> a[i];
    }
    vector<tuple<int, int, int>> qs;
    rep(i, 0, q){
        int l, x; cin >> l >> x; l--;
        qs.emplace_back(l, x, i);
    }
    sort(all(qs));
    int pnt = 0;
    vl ans(q);
    for(auto [l, x, idx] : qs){
        while(pnt <= l){
            v.add(a[pnt++]);
        }
        if(v.indep(x)){
            ans[idx] = 0;
        }
        else ans[idx] = modpow(2, v.nfree);
    }
    for(ll i : ans) cout << i << nL;

    
    return 0;
}
