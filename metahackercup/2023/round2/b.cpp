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
	HashInterval(vi& str) : ha(sz(str)+1), pw(ha) {
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
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n; cin >> n;
        // n *= 2;
        vi a(2 * n);
        rep(i, 0, 2 * n) cin >> a[i];
        set<int> ss;
        rep(i, 0, 2 * n) ss.insert(a[i]);
        unordered_map<int, int> rl;
        rl[-5] = 0;
        for(int i : ss) rl[i] = sz(rl);
        rep(i, 0, 2 * n) a[i] = rl[a[i]];
        vi ac(a);
        rep(i, 0, 2 * n) ac.pb(a[i]);
        vi reva(ac);
        reverse(all(reva));
        vi cond(2 * n);
        int windowsize = n / 2;
        int lt = 0, gt = 0;
        rep(i, 0, 2 * n + windowsize - 1){
            // rem previous
            if(i >= windowsize){
                lt -= ac[i - windowsize] < ac[(i - windowsize + n) % (2 * n)];
                gt -= ac[i - windowsize] > ac[(i - windowsize + n) % (2 * n)];
            }
            lt += ac[i % (2 * n)] < ac[(i + n) % (2 * n)];
            gt += ac[i % (2 * n)] > ac[(i + n) % (2 * n)];
            if(i >= windowsize - 1){
                int startleft = (i - (windowsize - 1) + 2 * n) % (2 * n);
                cond[startleft] += lt == windowsize;
                int startright = (i - (windowsize + (n % 2)) - (windowsize - 1) + 2 * n) % (2 * n);
                cond[startright] += gt == windowsize;
                if(gt == windowsize){
                    // cout << startright << " satisfies cond2" << endl;
                }
                if(lt == windowsize){
                    // cout << startleft << " satisfies cond1" << endl;
                }
                // cout << "current window from " << (i - (windowsize - 1)) << " to " << i << " " << lt << " " << gt << endl;
                // cout << "checked startleft of " << startleft << nL;
                // cout << "checked startright of " << startright << nL;
            }
        }
        // rep(i, 0, 2 * n){
        //     cout << i << " " << cond[i] << endl;
        // }
        HashInterval ahash(ac), revhash(reva);
        int ans = -1;
        rep(i, 0, 2 * n){
            if(cond[i] == 2 && ahash.hashInterval(i, i + n) == revhash.hashInterval(2 * n - i, 2 * n - i + n)){
                if(ans == -1 || i < ans) ans = i;
            }
        }
        cout << "Case #" << (cn + 1) << ": " << ans << nL;
    }
    
    return 0;
}
