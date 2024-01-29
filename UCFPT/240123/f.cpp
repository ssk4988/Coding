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
    vi x, y;
    int n;
    vector<FT> ft;
    vi freq(10);
    set<int> inc;
    {
        string xstr, ystr; cin >> xstr >> ystr;
        n = sz(xstr);
        ft = vector<FT>(10, FT(n));
        x = vi(n), y = vi(n);
        rep(i, 0, n){
            x[i] = xstr[i] - '0';
            y[i] = ystr[i] - '0';
            freq[x[i]]++;
            ft[y[i]].update(i, 1);
        }
        rep(i, 0, n - 1){
            if(y[i] < y[i + 1]) inc.insert(i);
        }
    }
    auto finddig = [&](int mod, int dig) -> int {
        vi freq1(freq);
        rep(i, 0, 10){
            freq1[i] -= ft[i].query(mod);
            assert(freq1[i] >= 0);
        }
        int to = -1;
        rep(i, y[mod] + 1, 10){
            if(freq1[i]) {to = i; break;}
        }
        if(to == -1) return to;
        freq1[to]--;
        assert(freq1[to] >= 0);
        // if(mod == 1 && dig == 0)
        // cout << "findig to is " << to << "\n";
        if(dig < mod) return y[dig];
        if(dig == mod) return to;
        dig -= mod;
        rep(i, 0, 10){
            if(dig <= freq1[i]) return i;
            dig -= freq1[i];
        }
        assert(false);
        return -1;
    };
    int q; cin >> q;
    rep(_, 0, q){
        // cout << "starting query " << _ << endl;
        int t, idx; cin >> t >> idx; idx--;
        if(t == 1){
            int dig; cin >> dig;
            ft[y[idx]].update(idx, -1);
            if(inc.count(idx)) inc.erase(idx);
            if(inc.count(idx - 1)) inc.erase(idx - 1);
            y[idx] = dig;
            ft[y[idx]].update(idx, 1);
            if(idx + 1 < n && y[idx] < y[idx + 1]) inc.insert(idx);
            if(idx > 0 && y[idx - 1] < y[idx]) inc.insert(idx - 1);
        }
        else{
            int farthest = n;
            rep(i, 0, 10){
                int kth = ft[i].lower_bound(freq[i] + 1) - 1;
                // cout << "kth: " << kth << "\n";
                farthest = min(farthest, kth);
            }
            // cerr << "farthest: " << farthest << "\n";
            // cout << "ans: ";
            assert(farthest >= -1);
            // if(farthest < 0){
            //     cout << -1 << nL;
            //     continue;
            // }
            if(farthest >= n - 1){
                cout << y[idx] << nL;
                continue;
            }
            int next = farthest + 1;
            int ans = finddig(next, idx);
            if(ans != -1){
                cout << ans << nL;
                continue;
            }
            if(farthest < 0){
                cout << -1 << nL;
                continue;
            }
            if(inc.count(farthest)){
                ans = finddig(farthest, idx);
                if(ans != -1) {cout << ans << nL; continue; }

            }
            auto it = inc.lower_bound(farthest);
            if(it == inc.begin()){
                cout << -1 << nL;
                continue;
            }
            it = prev(it);
            ans = finddig(*it, idx);
            cout << ans << "\n";
            // cout << "answered" << endl;
        }
    }
    
    return 0;
}
