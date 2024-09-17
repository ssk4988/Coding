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


struct SQRT {
	vi bs, ps, a;
	vvi pref, suff;
	vector<vvi> blocks;
	SQRT(vi a) : a(a) {
		int b = __lg(sz(a));
		int n = sz(a);
		for(; b; b = min(b-1, (b + 1) / 2)) bs.push_back(b), ps.push_back(1 << b);
		pref.resize(sz(bs), a), suff.resize(sz(bs), a); blocks.resize(sz(bs));
		rep(i, 0, sz(pref)) {
			rep(j, 0, n)
				if(j & (ps[i]-1)) pref[i][j] = min(pref[i][j-1], pref[i][j]);
			for(int j = n-1; j >= 0; j--)
				if((j+1) & (ps[i]-1)) suff[i][j] = min(suff[i][j], suff[i][j+1]);
		}
		rep(i, 0, sz(blocks)){
			// remove inclusive exclusive
			blocks[i] = vvi((n + ps[i] - 1) / ps[i], vi(ps[i], INT_MAX));

			for(int j = sz(blocks[i])-1; j >= 0; j--) {
				blocks[i][j][0] = suff[i][j * ps[i]];
				rep(k, 1, sz(blocks[i][j])) if(j+k <= sz(blocks[i])) blocks[i][j][k] = min(blocks[i][j][k-1], blocks[i][j+k-1][0]);
			}
		}
	}
	int query(int l, int r) {
		assert(l < r);
		if(r-l == 1) return a[l];
		if(r-l == 2) return min(a[l], a[l+1]);
		int i = 0;
		for(; ps[i] >= r - l; i++);
		int left = suff[i][l];
		// l = ((l >> bs[i]) + 1) << bs[i];
		l = (l | (ps[i]-1))+1;
		r--; // NOOOOOOOO
		int s = (r-l) / ps[i];
		if (s) left = min(left, blocks[i][l / ps[i]][s]);
		return min(left, pref[i][r]);
	}
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, q; cin >> n >> q; 
    vi a(n);
    rep(i,0,n){
        cin >> a[i];
    }
	SQRT t(a);
    rep(i, 0, q){
        int l, r; cin >> l >> r; l--;
        cout << t.query(l, r) << "\n";
    }
    
    
    return 0;
}
