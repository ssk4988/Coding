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
        vi a(n);
        FT ft(2*n);
        rep(i, 0, n) cin >> a[i];
        {
            vi b(a);
            sort(all(b));
            b.erase(unique(all(b)), end(b));
            rep(i, 0, n) a[i] = lower_bound(all(b), a[i]) - begin(b);
        }
        vi b(a);
        sort(all(b));
        vi jmp(n, n-1);
        for(int i = n-2; i >= 0; i--) {
            jmp[i] = a[i] <= a[i+1] ? jmp[i+1] : i;
        }
        // vi freqstart(n), freqend(n);
        bool works = true;
        ll ans = 1e18;
        map<pii, int> diff;
        rep(l, 1, n+1) {
            if(n % l) continue;
            for(int i = 0; i < n; i += l) {
                int j = i + l - 1;
                if(jmp[i] < j) works = false;
                // freqstart[a[i]]--, freqend[a[j]]--;
                // freqstart[b[i]]++, freqend[b[j]]++;
                diff[{a[i], a[j]}]--;
                diff[{b[i], b[j]}]++;
            }
            for(auto [k, v] : diff) if(v) works = false;
            // for(int i = 0; i < n; i += l) {
            //     int j = i + l - 1;
            //     if(freqstart[a[i]] || freqstart[b[i]] || freqend[a[j]] || freqend[b[j]]) {
            //         works = false;
            //         // cerr << i << " to " << j << " breaks " << l << endl;
            //         break;
            //     }
            // }
            if(works) {
                // cerr << l << " works" << endl;
                ll inv = 0;
                for(int i = 0; i < 3 * n; i += l) {
                    if(i >= n) {
                        int u1 = a[(i-n) % n], v1 = a[(i + l-1 - n) % n];
                        inv -= ft.query(2 * u1 + (u1 != v1));
                        ft.update(2 * u1 + (u1 != v1), -1);
                    }
                    if(i < 2 * n) {
                        int u = a[i % n], v = a[(i + l-1) % n];
                        inv += ft.query(2*n) - ft.query(2*u + (u != v)+1);
                        ll cur = (i/l+1)%(n/l) + inv;
                        // cerr << i << " " << i/l%n << " " << cur << " " << inv << endl;
                        if(i >= n) ans = min(ans, cur);
                        ft.update(2*u+(u!=v), 1);
                    }
                }
            }
            // for(int i = 0; i < n; i += l) {
            //     int j = i + l - 1;
            //     freqstart[a[i]] = 0, freqend[a[j]] = 0;
            //     freqstart[b[i]] = 0, freqend[b[j]] = 0;
            // }
        }
        cout << ans << "\n";
    }

    
    return 0;
}
