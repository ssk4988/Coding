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

struct V {
    ll v;
    V(ll x=0) : v(x) {}
    V operator+(V o) { return v + o.v; }
};
template<typename T>
struct SQRT {
	vi bits, pows, t;
    vector<T> a;
	vector<vector<T>> pref, suff;
	vector<vector<vector<T>>> blocks;
	SQRT(vector<T> a) : a(a) {
		int b = __lg(sz(a)), n = sz(a);
		for(; b; b = min(b-1, (b + 1) / 2)) bits.push_back(b), pows.push_back(1 << b);
		pref.resize(sz(bits), a), suff.resize(sz(bits), a), blocks.resize(sz(bits));
		rep(i, 0, sz(bits)) {
			rep(j, 0, n)
				if(j & (pows[i]-1)) pref[i][j] = pref[i][j-1] + pref[i][j];
			for(int j = n-1; j >= 0; j--)
				if((j+1) & (pows[i]-1)) suff[i][j] = suff[i][j] + suff[i][j+1];
            
            blocks[i].assign(n / pows[i], vector<T>(pows[i]));
			for(int j = sz(blocks[i])-1; j >= 0; j--) {
				blocks[i][j][0] = suff[i][j * pows[i]];
				rep(k, 1, sz(blocks[i][j])) if(j+k < sz(blocks[i])) blocks[i][j][k] = blocks[i][j][k-1] + blocks[i][j+k][0];
			}
		}
        t.resize(30, sz(bits)-1);
        rep(i, 0, sz(t)) while(t[i] && i > bits[t[i]-1]) t[i]--;
	}
	T query(int l, int r) {
		assert(l < r);
		if(r-l == 1) return a[l];
		if(r-l == 2) return a[l] + a[l+1];
        int i = t[__lg(r - l) + (__builtin_popcount(r-l) != 1)];
		T left = suff[i][l];
		r--, l = (l | (pows[i]-1))+1;
		int s = (r-l) / pows[i];
		if(s) left = left + blocks[i][l / pows[i]][s-1];
		return left + pref[i][r];
	}
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, q; cin >> n >> q; 
    vector<V> a(n);
    rep(i,0,n){
        cin >> a[i].v;
    }
	SQRT<V> t(a);
    rep(i, 0, q){
        int l, r; cin >> l >> r;
        cout << t.query(l, r).v << "\n";
    }
    
    
    return 0;
}
