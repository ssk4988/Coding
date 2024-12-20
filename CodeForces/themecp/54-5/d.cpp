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
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        int n; cin >> n;
        string s; cin >> s;
        FT cnt(3*n), pcnt(3*n);
        vi a(n);
        rep(i, 0, n) a[i] = s[i] == '(' ? 1 : -1;
        vi pref(a);
        partial_sum(all(pref), begin(pref));
        pref.insert(begin(pref), 0);
        ll ans = 0;
        vll st;
        st.push_back({-1e9, sz(pref)});
        ll cur = 0;
        for(int i = sz(pref)-1; i >= 0; i--) {
            pll nxt{pref[i], i};
            while(sz(st) && nxt < st.back()) {
                if(sz(st) >= 2) cur -= st[sz(st)-1].f * (st[sz(st)-2].s - st.back().s);
                st.pop_back();
            }
            cur += pref[i] * (st.back().s - i);
            st.pb(nxt);
            ans += pref[i] * (sz(pref) - i) - cur;
        }
        rep(i, 0, sz(pref)){
            ll c = cnt.query(n+pref[i]);
            ll sm = pcnt.query(n+pref[i]);
            ans += c * pref[i] - sm;
            cnt.update(n+pref[i], 1);
            pcnt.update(n+pref[i], pref[i]);
        }
        cout << ans << "\n";
    }
    
    return 0;
}
