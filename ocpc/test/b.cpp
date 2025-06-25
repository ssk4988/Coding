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


bool comp(int x, int y) {
    return x > y;
}
void test(vi arr) {
    int n = arr.size();
    ll ans = 0;
    int did = 0;
    for(int iter = 0; iter < n-1; iter++) {
        did++;
        bool done_sorting = true;
        for(int i = 0; i < n-1; i++) {
            ans++;
            if(comp(arr[i], arr[i+1])) {
                done_sorting = false;
                swap(arr[i], arr[i+1]);
                ans++;
            }
        }

        for(int i = n-1; i > 0; i--) {
            ans++;
            if(comp(arr[i-1], arr[i])) {
                done_sorting = false;
                swap(arr[i-1], arr[i]);
                ans++;
            }
        }
        rep(i, 0, n) cerr << arr[i] << " ";
        cerr << endl;
        
        if(done_sorting) break;
    }
    cerr << "rounds: " << did << " ops: " << ans << endl;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vi a(n);
    vii b;
    rep(i, 0, n) {
        cin >> a[i];
        b.push_back(pii{a[i], i});
    }
    sort(all(b));
    rep(i, 0, n) a[b[i].s] = i;
    // rep(i, 0, n) cerr << a[i] << " ";
    // cerr << endl;
    // test(a);
    vi inv(n);
    rep(i, 0, n) inv[a[i]] = i;
    ll ans = 0;
    FT zero(n), one(n);
    rep(i, 0, n) {
        one.update(i, 1);
    }
    int cur = 0;
    rep(i, 0, n) {
        // cerr << "starting v=" << i << " idx=" << inv[i] << endl;
        one.update(inv[i], -1);
        zero.update(inv[i], 1);
        while(cur > min(i+1, n-1-i) || one.lower_bound(cur) >= zero.lower_bound(i+1+1-cur)) {
            cur--;
        }
        while(cur < min(i+1, n-1-i) && one.lower_bound(cur+1) < zero.lower_bound(i+1+1-(cur+1))) {
            cur++;
        }
        ans = max(ans, ll(cur));
    }
    FT ft(n);
    vi left(n), right(n);
    ll inversions = 0;
    rep(i, 0, n) {
        left[i] = ft.query(n) - ft.query(a[i]);
        ft.update(a[i], 1);
        inversions += left[i];
    }
    ans++;
    // cerr << "my rounds: " << ans << " " << ans*(n-1+n-1) << " " << inversions << endl;
    cout << ans*(n-1+n-1)+inversions << "\n";
    return 0;
}
