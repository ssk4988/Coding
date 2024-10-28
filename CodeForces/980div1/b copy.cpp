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
        vl a(n);
        FT ft(n);
        rep(i, 0, n){
            cin >> a[i];
            ft.update(i, a[i]);
        }
        vi b(n);
        rep(i,0,n){
            cin >> b[i]; b[i]--;
        }
        set<int> left;
        rep(i, 0, n) left.insert(i);
        int cur = 0;
        ll curv = 0;
        ll best = 0;
        while(true){
            best = max(best, curv + ft.query(cur+1));
            left.erase(cur);
            ft.update(cur, -a[cur]);
            if(b[cur] <= cur){
                curv += a[cur];
                auto it = left.upper_bound(cur);
                if(it != begin(left)) {
                    it = prev(it);
                    cur = *it;
                } else break;
            } else {
                auto it = left.upper_bound(b[cur]);
                if(it != begin(left)) {
                    it = prev(it);
                    if(*it < cur) curv+= a[cur];
                    cur = *it;
                } else break;
            }
        }
        cout << best << "\n";
    }
    
    return 0;
}
