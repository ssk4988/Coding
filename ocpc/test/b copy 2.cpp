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

0101010
0010101
0001011

110100100

it 1
101001001
010100101

it 2
001001011
000100111

when moving right: each 1 goes immediately to the left of the next one
when moving left: each 0 goes immediately to the right of the previous 0

101011011
it 1
010110111
001011111
it 2



1101110
it 1
1011101
0101111

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
        b.push_back(pii{a[i], i});
    }
    sort(all(b));
    rep(i, 0, n) a[b[i].s] = i;
    rep(i, 0, n) cerr << a[i] << " ";
    cerr << endl;
    test(a);
    vi inv(n);
    rep(i, 0, n) inv[a[i]] = i;
    ll ans = 0;
    rep(iters, 0, 2) {
        cerr << "iters: " << iters << endl;
        int pref0 = 0;
        set<int> left;
        set<pii> right;
        vi is(n, 1);
        auto shiftleft = [&]() -> void {
            auto [l, r] = *begin(right);
            right.erase(begin(right));
            left.insert(l);
            if(l < r) right.insert(pii{l+1, r});
        };
        rep(i, 0, n) {
            // cerr << "starting v=" << i << " idx=" << inv[i] << endl;
            is[inv[i]] = 0;
            if(inv[i] == pref0) {
                left.insert(inv[i]);
                while(pref0 < n && is[pref0] == 0) {
                    if(!sz(left)) shiftleft();
                    left.erase(begin(left));
                    pref0++;
                }
            }
            // cerr << "left: ";
            // for(int l : left) cerr << l << " ";
            // cerr << endl;
            // cerr << "right: ";
            // for(auto [l, r] : right) cerr << l << "," << r << " ";
            // cerr << endl;
            if(inv[i] >= pref0)
            {
                int l = inv[i], r = inv[i];
                auto it = right.upper_bound(pii{l, r});
                if(it != end(right) && it->f == r+1) {
                    r = it->s;
                    right.erase(it);
                }
                it = right.upper_bound(pii{l, r});
                if(it != begin(right) && it->s == l-1) {
                    it--;
                    l = it->f;
                    right.erase(it);
                }
                right.insert(pii{l, r});
            }

            while(sz(left) > sz(right)) {
                auto v = *rbegin(left);
                left.erase(prev(end(left)));
                if(sz(right) && begin(right)->f == 1+v) {
                    auto [l, r] = *begin(right);
                    right.erase(begin(right));
                    right.insert(pii{v, r});
                } else right.insert({v, v});
            }
            while(sz(left) < sz(right)) {
                shiftleft();
            }
            cerr << "i=" << i << " a=";
            rep(i, 0, n) cerr << is[i] << " ";
            cerr << " cur: " << sz(left) << endl;
            ans = max(ans, ll(sz(left)));
            // cerr << "left: ";
            // for(int l : left) cerr << l << " ";
            // cerr << endl;
            // cerr << "right: ";
            // for(auto [l, r] : right) cerr << l << "," << r << " ";
            // cerr << endl;
        }
        reverse(all(inv));
        rep(i, 0, n) inv[i] = n-1-inv[i];
    }
    FT ft(n);
    vi left(n), right(n);
    ll inversions = 0;
    rep(i, 0, n) {
        left[i] = ft.query(n) - ft.query(a[i]);
        ft.update(a[i], 1);
        inversions += left[i];
    }
    // ft = FT(n);
    // for(int i = n-1; i >= 0; i--) {
    //     right[i] = ft.query(a[i]);
    //     ft.update(a[i], 1);
    // }
    // rep(i, 0, n) cerr << left[i] << " ";
    // cerr << endl;
    // rep(i, 0, n) cerr << right[i] << " ";
    // cerr << endl;
    // ll ans = 0;
    // rep(i, 0, n) {
    //     ans = max(ans, 1+ll(min(left[i], right[i]) + (left[i] != right[i])));
    // }
    cerr << "my rounds: " << ans << " " << ans*(n-1+n-1) << " " << inversions << endl;
    cout << ans*(n-1+n-1)+inversions << "\n";
    return 0;
}
