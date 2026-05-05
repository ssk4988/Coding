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

struct FT {
	vector<ll> s;
	FT(int n) : s(n) {}
	void update(int pos, ll dif) { // a[pos] += dif
		for (; pos < sz(s); pos |= pos + 1) s[pos] += dif;
	}
	ll query(int pos) { // sum of values in [0, pos)
		ll res = 0;
		for (; pos > 0; pos &= pos - 1) res += s[pos-1];
		return res;
	}
	int lower_bound(ll sum) {// min pos st sum of [0, pos] >= sum
		// Returns n if no sum is >= sum, or -1 if empty sum is.
		if (sum <= 0) return -1;
		int pos = 0;
		for (int pw = 1 << 25; pw; pw >>= 1) {
			if (pos + pw <= sz(s) && s[pos + pw-1] < sum)
				pos += pw, sum -= s[pos-1];
		}
		return pos;
	}
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, q; cin >> n >> q;
    vi a(n);
    rep(i, 0, n) cin >> a[i];
    int ops = 0;
    rep(i, 0, n) {
        if(i < n-1-i && a[i] != a[n-1-i]) ops++;
    }
    vi b(a);
    sort(all(b));
    b.erase(unique(all(b)), end(b));
    bool dup = sz(b) < sz(a);

    // FT ft(n);
    // ll inv = 0;
    // vi freq(n);
    // rep(i, 0, n) {
    //     a[i] = lower_bound(all(b), a[i]) - begin(b);
    //     inv += ft.query(n) - ft.query(a[i]);
    //     ft.update(a[i], 1);
    //     freq[a[i]]++;
    // }
    // b = a;
    // sort(all(b));
    // reverse(all(b));
    // cerr << "inv " << inv << endl;
    // rep(i, 0, n) cerr << b[i] << ",";
    // cerr << endl;
    // rep(i, 0, n) cerr << a[i] << ",";
    // cerr << endl;
    // int ops = 0;
    // vi start(n);
    // for(int i = n-2; i >= 0; i--) {
    //     start[i] = start[i+1] + freq[i+1];
    // }
    // rep(i, 0, n) {
    //     while(a[i] != b[i]) {
    //         while(a[start[a[i]]] == a[i]) start[a[i]]++;
    //         int j = start[a[i]];
    //         // cerr << "j=" << j << endl;
    //         swap(a[i], a[j]);
    //         ops++;
    //         // rep(j, 0, n) cerr << a[j] << ",";
    //         // cerr << endl;
    //     }
    //     cerr << "fixed " << i << endl;
    // }
    cerr << "ops=" << ops << endl;
    rep(qid, 0, q) {
        int k; cin >> k;
        if(ops > k || (!dup && (k & 1) != (ops & 1))) cout << "NO\n";
        else cout << "YES\n";
    }

    
    return 0;
}
