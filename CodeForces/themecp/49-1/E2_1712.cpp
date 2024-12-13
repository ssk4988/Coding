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

ll nc3(ll x){
    return x * (x-1) * (x-2) / 6;
}
ll nc2(ll x) {
    return x * (x-1) / 2;
}

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
    const int LIM = 4e5+20;
    vvi divs(LIM);
    FT ft(LIM);
    rep(i, 1, LIM){
        for(int j = i; j < LIM; j += i){
            divs[j].pb(i);
        }
    }
    vector<array<ll, 3>> queries;
    vl ans(nc);
    rep(cn, 0, nc){
        ll l, r; cin >> l >> r; r++;
        queries.pb({r, l, cn});
    }
    sort(all(queries));
    int k = 1;
    for(auto [r, l, qi] : queries){
        ll curans = nc3(r-l);
        while(k < r) {
            for(int i = sz(divs[k])-2; i >= 0; i--){
                ft.update(divs[k][i], sz(divs[k])-2-i);
            }
            int p = 1;
            while(k % (p * 2) == 0) p *= 2;
            p *= 2;
            for(int i : divs[2 * k]) {
                if (i >= k) continue;
                for(int j : divs[2 * k]) {
                    if (j >= i) continue;
                    if((i % p == 0 || j % p == 0) && i + j > k){
                        ft.update(j, 1);
                    }
                }
            }
            k++;
        }
        curans -= (ft.query(r) - ft.query(l));
        ans[qi] = curans;
    }
    rep(cn, 0, nc){
        cout << ans[cn] << "\n";
    }

    
    return 0;
}
