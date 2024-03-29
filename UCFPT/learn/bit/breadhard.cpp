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
    int n; cin >> n;
    vi order(n), perm(n);
    rep(i, 0, n){
        cin >> order[i]; order[i]--;
    }
    rep(i, 0, n){
        int x; cin >> x; x--;
        perm[x] = i;
    }
    FT ft(n);
    set<int> ss;
    vi rev(n);
    rep(i, 0, n){
        ft.update(i, 1);
        ss.insert(i);
        order[i] = perm[order[i]];
        rev[order[i]] = i;
        // cout << i << " " << order[i] << "\n";
    }
    rep(i, 0, n-3){
        int place = rev[i];
        ft.update(place, -1);
        ss.erase(place);
        if(ft.query(place) % 2){
            int one = *ss.begin(), two = *next(ss.begin());
            swap(order[one], order[two]);
            swap(rev[order[one]], rev[order[two]]);
        }
    }
    vi left;
    for(int i : ss){
        left.pb(order[i]);
    }
    while(left[0] > min(left[1], left[2])){
        rotate(left.end()-3, left.end() - 2, left.end());
    }
    if(left[0] < left[1] && left[1] < left[2]){
        cout << "Possible\n";
    }
    else cout << "Impossible\n";
    

    
    return 0;
}
