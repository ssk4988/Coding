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

typedef uint64_t ull;
static int C; // initialized below

// Arithmetic mod two primes and 2^32 simultaneously.
template<int M, class B>
struct A {
	int x; B b; A(int x=0) : x(x), b(x) {}
	A(int x, B b) : x(x), b(b) {}
	A operator+(A o){int y = x+o.x; return{y - (y>=M)*M, b+o.b};}
	A operator-(A o){int y = x-o.x; return{y + (y< 0)*M, b-o.b};}
	A operator*(A o) { return {(int)(1LL*x*o.x % M), b*o.b}; }
	explicit operator ull() { return x ^ (ull) b << 21; }
	bool operator==(A o) const { return pair{x, b} == pair{o.x, o.b}; }
	bool operator<(A o) const { return (ull)*this < (ull)o; }
};
// typedef A<1000000007, A<1000000009, unsigned>> H;
typedef A<1000000009, unsigned> H;
// "typedef uint64_t H;" instead if Thue-Morse does not apply.

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

vector<H> getHashes(string& str, int length) {
	if (sz(str) < length) return {};
	H h = 0, pw = 1;
	rep(i,0,length)
		h = h * C + str[i], pw = pw * C;
	vector<H> ret = {h};
	rep(i,length,sz(str)) {
		ret.push_back(h = h * C + str[i] - pw * str[i-length]);
	}
	return ret;
}

H hashString(string& s){H h{}; for(char c:s) h=h*C+c;return h;}

ll euclid(ll a, ll b, ll &x, ll &y) {
	if (!b) return x = 1, y = 0, a;
	ll d = euclid(b, a % b, y, x);
	return y -= a/b * x, d;
}

bool hasNonNegSol(ll a, ll b, ll c) {
    // non-neg x, y such that ax + by = c
    ll g = gcd(a, b);
    if(c % g != 0) return false;
    if(g != 1) return hasNonNegSol(a/g, b/g, c/g);
    ll x, y;
    g = euclid(a, b, x, y);
    // ax + by = 1
    x *= c, y *= c;
    ll targetx = (x % b + b) % b;
    ll diff = (targetx - x) / b;
    x += diff * b;
    y -= diff * a;
    return x >= 0 && y >= 0;
}

vector<string> output;

void solve(int cn) {
    int n, m; cin >> n >> m;
    string a, b; cin >> a >> b;
    HashInterval ha(a), hb(b);
    string res;
    int period = m;
    for(int i = 1; i < m; i++) {
        if(m % i != 0) continue;
        int make = 0;
        while(make < m && hb.hashInterval(0, i) == hb.hashInterval(make, make + i)) make += i;
        if(make == m) {
            period = i;
            break;
        }
    }
    bool periodmatch = false;
    {
        int make = 0;
        while(period <= n && make + period <= m && ha.hashInterval(0, period) == hb.hashInterval(make, make + period)) make += period;
        if(make == m) {
            periodmatch = true;
        }
    }
    rep(i, 1, n){
        H hsmall = ha.hashInterval(0, i), hbig = ha.hashInterval(i, n);
        pii small = {i, 0}, big = {n-i, i};
        if(small > big){
            swap(small, big);
            swap(hsmall, hbig);
        }
        int lcp = 0;
        while(lcp < big.f) {
            H bigh;
            if(lcp + small.f > big.f) {
                int extra = lcp + small.f - big.f;
                bigh = ha.hashInterval(big.s + lcp, big.s + big.f) * ha.pw[extra] + ha.hashInterval(big.s, big.s + extra);
            } else bigh = ha.hashInterval(big.s + lcp, big.s + lcp + small.f);
            if(bigh == hsmall) lcp += small.f;
            else break;
        }
        int idx = 0;
        bool checkextra = false;
        H extrah;
        int extra = lcp + small.f - big.f;
        if(lcp > big.f) {
            bool works = hasNonNegSol(small.f, big.f, m);
            // cout << small.f << " " << big.f << " " << works << endl;
            if(works && gcd(big.f, small.f) % period == 0 && periodmatch) res += "1";
            else res += "0";
            continue;
        } else if (lcp + small.f > big.f && lcp != big.f) {
            // cout << "diverge " << small.f << " " << big.f << " " << lcp << endl;
            checkextra = true;
            extrah = ha.hashInterval(big.s + lcp, big.s + big.f) * ha.pw[extra] + ha.hashInterval(big.s, big.s + extra);
            assert(!(extrah == hsmall));
            assert(big.f + extra == lcp + small.f);
        }
        while(idx < m) {
            if(big.f + idx <= m && hbig == hb.hashInterval(idx, idx + big.f)) {
                if(checkextra && idx + big.f + extra <= m) {
                    if(hsmall == hb.hashInterval(idx + lcp, idx + lcp + small.f)) idx += small.f;
                    else idx += big.f;
                } else 
                idx += big.f;
            } else if(small.f + idx <= m && hsmall == hb.hashInterval(idx, idx + small.f)) {
                idx += small.f;
            } else break;
        }
        if(idx == m) res += "1";
        else res += "0";
    }
    output.pb(res);
    // if(cn == 48848) {
    //     output.insert(begin(output), a + " " + b);
    // }
}

#include <sys/time.h>
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    timeval tp;
	gettimeofday(&tp, 0);
	C = (int)tp.tv_usec; // (less than modulo)
	assert((ull)(H(1)*2+1-3) == 0);
    int nc; cin >> nc;
    rep(cn, 0, nc)
    solve(cn+1);
    for(auto &a : output) cout << a << "\n";
    return 0;
}
