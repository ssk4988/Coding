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
const int inf = 1e9;
struct Tree {
	typedef pii T;
	static constexpr T unit = {inf, -1};
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
    rep(cn, 0, nc) {
        int n; cin >> n;
        vi a(n), b(n);
        a.push_back(inf);
        rep(i, 0, n) cin >> a[i];
        rep(i, 0, n) cin >> b[i];
        vi st{n};
        Tree tree(n);
        rep(i, 0, n) {
            tree.update(i, pii{b[i], i});
        }
        ll ans = 0, cur = 0, delta = 0;
        vi rem(n);
        for(int i =n-1; i >= 0; i--) {
            // cur += delta;
            while(a[st.back()] <= a[i]) {
                int j = st.back();
                st.pop_back();
                cur -= (a[j] == b[j]) * (n-j);
                // if(a[j] >= b[j]) {
                //     rem[j] = 1;
                // }
                assert(rem[j] == 0);
                // delta += rem[j];
                // cur += rem[j] * (n-j);
            }
            // cerr << "cur before " << i << " " << cur << endl;
            int j = st.back();
            cur += (a[i] == b[i]) * (n-i);
            while(true) {
                auto [v, k] = tree.query(i+1, j);
                if(v == inf || v > a[i]) break;
                assert(rem[k] == 0);
                // cerr << "rem " << k << endl;
                rem[k] = 1;
                tree.update(k, pii{inf, -1});
                delta++;
                cur += (n-k);
            }
            st.push_back(i);
            ans += cur;
            // cerr << i << " delta" << delta << " cur" << cur << " ans" << ans << ": ";
            // for(int v : st) cout << v << "," << a[v] << " ";
            // cerr << endl;
        }
        cout << ans << "\n";
    }
    
    
    return 0;
}
