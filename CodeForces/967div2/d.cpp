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
using vll = vector<pll>;;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

struct Tree {
	typedef pii T;
	static constexpr T unit = {INT_MAX, INT_MAX};
	T f(T a, T b) { return min(a, b); } // (any associative fn)
	vector<T> s; int n;
	Tree(int n = 0, T def = unit) : s(2*n, def), n(n) {}
	void update(int pos, T val) {
		for (s[pos += n] = val; pos /= 2;)
			s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
	}
	T query(int b, int e) { // query [b, e)
		T ra = unit, rb = unit;
		for (b += n, e += n; b < e; b /= 2, e /= 2) {
			if (b % 2) ra = f(ra, s[b++]);
			if (e % 2) rb = f(s[--e], rb);
		}
		return f(ra, rb);
	}
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n; cin >> n;
        vi lastocc(n+1, -1);
        vvi occ(n+1);
        vi a(n);
        rep(i, 0, n) {
            cin >> a[i];
            lastocc[a[i]] = i;
            occ[a[i]].pb(i);
        }
        set<int> pos;
        // set<pii> mnv, mxv;
        rep(i, 0, sz(lastocc)){
            if(lastocc[i] != -1){
                pos.insert(lastocc[i]);
            }
        }
        Tree mn(n), mx(n);
        rep(i, 0, n){
            mn.update(i, {a[i], i});
            mx.update(i, {-a[i], i});
        }

        int start = 0;
        vi seq;
        while(sz(pos)) {
            int end = *pos.begin() + 1;
            // cout << "range: " << start << " " << end << "\n";
            auto [val, idx] = (sz(seq) % 2 == 0 ? mx : mn).query(start, end);
            // cout << val << " " << idx << "\n";
            seq.pb(a[idx]);
            pos.erase(lastocc[a[idx]]);
            for(int i : occ[a[idx]]){
                mn.update(i, mn.unit);
                mx.update(i, mx.unit);
            }
            start = idx+1;
        }
        cout << sz(seq) << "\n";
        for(int i : seq) cout << i << " ";
        cout << "\n";
    }
    
    return 0;
}
