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
using vll = vector<pll>;;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

vi Z(const string& S) {
	vi z(sz(S));
	int l = -1, r = -1;
	rep(i,1,sz(S)) {
		z[i] = i >= r ? 0 : min(r - i, z[i - l]);
		while (i + z[i] < sz(S) && S[i + z[i]] == S[z[i]])
			z[i]++;
		if (i + z[i] > r)
			l = i, r = i + z[i];
	}
	return z;
}
typedef uint64_t ull;
struct H {
	ull x; H(ull x=0) : x(x) {}
	H operator+(H o) { return x + o.x + (x + o.x < x); }
	H operator-(H o) { return *this + ~o.x; }
	H operator*(H o) { auto m = (__uint128_t)x * o.x;
		return H((ull)m) + (ull)(m >> 64); }
	ull get() const { return x + !~x; }
	bool operator==(H o) const { return get() == o.get(); }
	bool operator<(H o) const { return get() < o.get(); }
};
static const H C = (ll)1e11+3; // (order ~ 3e9; random also ok)

struct HashInterval {
	vector<H> ha, pw;
	HashInterval(string& str) : ha(sz(str)+1), pw(ha) {
		pw[0] = 1;
		rep(i,0,sz(str))
			ha[i+1] = ha[i] * C + str[i],
			pw[i+1] = pw[i] * C;
	}
	H hashInterval(int a, int b) { // hash [a, b)
		return ha[b] - ha[a] * pw[b - a];
	}
};


int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    string str; cin >> str;
    string fr = str.substr(0, n/2), ba = str.substr(n - n/2);
    str = fr + "$" + ba;
    // cout << str << "\n";
    n = sz(str);
    HashInterval ha(str);
    vi z = Z(str);
    int n2 = n / 2;
    int ans = 0;
    vi cand;
    vi ends;
    for(int i = n - 1; i > n2; i--){
        if(i + z[i] == n){
            ans = max(ans, z[i]);
            if(sz(ends) <= 1){
                cand.pb(i);
            }
            else if(ends[sz(ends) - 1] - i != ends[sz(ends) - 2] - ends[sz(ends) - 1]) {
                cand.pb(ends[sz(ends) - 1]);
            }
            ends.pb(i);
        }
    }
    for(int idx : cand){
        int len = n - idx;
        rep(len2, 1, n2 - len + 1){
            if(ha.hashInterval(len, len + len2) == ha.hashInterval(idx - len2, idx)){
                ans = max(ans, len + len2);
            }
        }
    }
    cout << ans << "\n";

    return 0;
}
