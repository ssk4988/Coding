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

/*
101011011
010110111
001011111

1010110
0101101
10110
01011
10

right:
rem rightmost one, delete left zero comp
left:
rem leftmost zero, delete right one comp

keep components of 1s on right balanced with single 1s on left

001100110011
right:
001001100111
left:
000100110111

11110000
11100001
01110001
00110011
00010111



when moving right: each 1 goes immediately to the left of the next one
when moving left: each 0 goes immediately to the right of the previous 0
*/

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vi a(n);
    vii b;
    rep(i, 0, n) {
        cin >> a[i];
        b.push_back({a[i], i});
    }
    sort(all(b));
    rep(i, 0, n) a[b[i].s] = i;
    rep(i, 0, n) cerr << a[i] << " ";
    cerr << endl;
    test(a);
    FT ft(n);
    vi left(n), right(n);
    ll inv = 0;
    rep(i, 0, n) {
        left[i] = ft.query(n) - ft.query(a[i]);
        ft.update(a[i], 1);
        inv += left[i];
    }
    ft = FT(n);
    for(int i = n-1; i >= 0; i--) {
        right[i] = ft.query(a[i]);
        ft.update(a[i], 1);
    }
    rep(i, 0, n) cerr << left[i] << " ";
    cerr << endl;
    rep(i, 0, n) cerr << right[i] << " ";
    cerr << endl;
    ll ans = 0;
    rep(i, 0, n) {
        ans = max(ans, 1+ll(min(left[i], right[i]) + (left[i] != right[i])));
    }
    cerr << "my rounds: " << ans << " " << ans*(n-1+n-1) << " " << inv << endl;
    cout << ans*(n-1+n-1)+inv << "\n";
    return 0;
}
