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

int maxbound = 5e5 + 10;
vi ordering;

bool cmp(vi &a, vi &b){
    for(int i : ordering){
        if(a[i] != b[i]) return a[i] < b[i];
    }
    return false;
}

struct FT {
	vector<int> s;
    vector<int> updates;
	FT(int n) : s(n) {}
	void update(int pos, int dif) { // a[pos] += dif
		for (; pos < sz(s); pos |= pos + 1) s[pos] += dif;
        updates.pb(pos);
	}
	int query(int pos) { // sum of values in [0, pos)
		int res = 0;
		for (; pos > 0; pos &= pos - 1) res += s[pos-1];
		return res;
	}
	int lower_bound(int sum) {// min pos st sum of [0, pos] >= sum
		// Returns n if no sum is >= sum, or -1 if empty sum is.
		if (sum <= 0) return -1;
		int pos = 0;
		for (int pw = 1 << 25; pw; pw >>= 1) {
			if (pos + pw <= sz(s) && s[pos + pw-1] < sum)
				pos += pw, sum -= s[pos-1];
		}
		return pos;
	}
    void clear(){
        for(int i : updates){
            update(i, -1);
        }
        // fill(all(s), 0);
    }
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, p, q, r;
    cin >> n >> p >> q >> r;
    ll ans = 0;
    vvi orders = {{0, 1}, {1, 2}, {0, 2}};
    vvi cards(n);
    rep(i, 0, n){
        int a, b, c; cin >> a >> b >> c;
        cards.pb({a, b, c});
    }
    FT ft(maxbound);
    rep(i, 0, sz(orders)){
        ordering = orders[i];
        ll ansorder = 0;
        sort(all(cards), cmp);
        for(vi &j : cards){
            ansorder += ft.query(j[ordering[1]]);
            ft.update(j[ordering[1]], 1);
        }
        ft.clear();
        cout << ansorder << nL;
        ans += ansorder;
    }
    cout << ans << nL;

    return 0;
}
