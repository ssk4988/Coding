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
    int n, m, q; cin >> n >> m >> q;
    string str; cin >> str;
    set<int> ss;
    FT ft(n);
    int cnt = 0;
    vi a(n);
    rep(i, 0, n){
        a[i] = str[i] - '0';
        ss.insert(i);
        cnt += a[i];
    }
    vi order;
    rep(i, 0, m){
        int l, r; cin >> l >> r;
        l--, r--;
        while(true){
            auto it = ss.lower_bound(l);
            if(it == ss.end() || *it > r) break;
            order.pb(*it);
            ss.erase(it);
        }
    }
    int v = sz(order);
    for(int i : ss) order.pb(i);
    unordered_map<int, int> rl;
    rep(i, 0, n){ 
        rl[order[i]] = i;
        ft.update(rl[order[i]], a[order[i]]);
    }
    rep(i, 0, q){
        int qi; cin >> qi;
        qi--;
        if(a[qi]) cnt--;
        else cnt++;
        ft.update(rl[qi], a[qi] ? -1 : 1);
        a[qi] = 1 - a[qi];
        int bitson = ft.query(min(v, cnt));
        cout << (min(v, cnt) - bitson) << nL;
    }
    
    return 0;
}