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

typedef uint64_t ull;
static int C; // initialized below

// Arithmetic mod two primes and 2^32 simultaneously.
// "typedef uint64_t H;" instead if Thue-Morse does not apply.
template<int M, class B>
struct A {
	int x; B b; A(int x=0) : x(x), b(x) {}
	A(int x, B b) : x(x), b(b) {}
	A operator+(A o){int y = x+o.x; return{y - (y>=M)*M, b+o.b};}
	A operator-(A o){int y = x-o.x; return{y + (y< 0)*M, b-o.b};}
	A operator*(A o) { return {(int)(1LL*x*o.x % M), b*o.b}; }
	explicit operator ull() { return x ^ (ull) b << 21; }
	bool operator==(A o) const { return pair<int, B>(this->x, this->b) == pair<int, B>(o.x, o.b); }
	bool operator<(A o) const { return pair<int, B>(this->x, this->b) < pair<int, B>(o.x, o.b); }
};
typedef A<1000000007, A<1000000009, unsigned>> H;

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
    rep(cn, 0, nc){
        string s; cin >> s;
        int n = sz(s);
        string o;
        vi oi, left, right;
        rep(i, 0, n){
            if(s[i] != 'a'){
                o.pb(s[i]);
                oi.pb(i);
                left.pb(0);
                right.pb(0);
                while(i + right.back() + 1 < n && s[i + right.back() + 1] == 'a') right.back()++;
                while(i - left.back() - 1 >= 0 && s[i - left.back() - 1] == 'a') left.back()++;
            }
        }
        if(sz(o) == 0){
            cout << n-1 << "\n";
            continue;
        }
        int k = sz(oi);
        HashInterval sh(s), oh(o);
        ll ans = 0;
        rep(len, 1, k+1){
            if(k % len != 0) continue;
            bool works = true;
            int mxl = n, mxr = n, mid = n;
            for(int i = 0; i < k; i += len){
                if(!(oh.hashInterval(i, i + len) == oh.hashInterval(0, len))){
                    works = false;
                }
                if(!(sh.hashInterval(oi[i], oi[i + len - 1] + 1) == sh.hashInterval(oi[0], oi[len - 1] + 1))){
                    works = false;
                }
                mxl = min(mxl, left[i]);
                mxr = min(mxr, right[i + len - 1]);
                if(i + len != k) mid = min(mid, right[i + len - 1]);
            }
            if(!works) continue;
            // 0 <= l <= mxl, 0 <= r <= mxr, l + r <= mid
            rep(l, 0, mxl + 1){
                if(mid - l < 0) break;
                ans += 1 + min(mxr, mid - l);
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}
