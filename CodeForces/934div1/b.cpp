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
	bool operator==(A o) const { return pair<int, B>(x, b) == pair<int, B>(o.x, o.b); }
	bool operator<(A o) const { return pair<int, B>(x, b) < pair<int, B>(o.x, o.b); }
};
typedef A<1000000007, A<1000000009, unsigned>> H;

struct HashInterval {
	vector<H> ha, rha, pw;
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

    // add 1
    // odd: if two classes same then no other odds, otherwise check largest odd if its whole range
    // even: if all same, then no evens, otherwise check largest even if its whole range
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n, q; cin >> n >> q;
        string str; cin >> str;
        string rstr(str);
        reverse(all(rstr));
        HashInterval ha(str), rha(rstr);
        vvi freq(26, vi(n));
        vector<vvi> freq2(2, vvi(26, vi(n)));
        vvi cnt(2, vi(n));
        rep(i, 0, n){
            freq[str[i] - 'a'][i]++;
            freq2[i % 2][str[i] - 'a'][i]++;
            cnt[i % 2][i]++;
        }
        rep(i, 0, 26){
            freq[i].insert(freq[i].begin(), 0);
            partial_sum(all(freq[i]), freq[i].begin());
            freq2[0][i].insert(freq2[0][i].begin(), 0);
            partial_sum(all(freq2[0][i]), freq2[0][i].begin());
            freq2[1][i].insert(freq2[1][i].begin(), 0);
            partial_sum(all(freq2[1][i]), freq2[1][i].begin());
        }
        cnt[0].insert(cnt[0].begin(), 0);
        partial_sum(all(cnt[0]), cnt[0].begin());
        cnt[1].insert(cnt[1].begin(), 0);
        partial_sum(all(cnt[1]), cnt[1].begin());
        rep(_, 0, q){
            int l, r; cin >> l >> r; l--;
            ll ans = 0;
            // CHECK LONGS
            bool allsame1 = false;
            bool allsame2o = false, allsame2e = false;
            rep(i, 0, 26){
                // if((r - l) % 2 == 0){
                bool cond2e = freq2[0][i][r] - freq2[0][i][l] == cnt[0][r] - cnt[0][l];
                bool cond2o = freq2[1][i][r] - freq2[1][i][l] == cnt[1][r] - cnt[1][l];
                allsame2e = allsame2e || cond2e;
                allsame2o = allsame2o || cond2o;
                // if(cond2) {
                //     cout << "cond2 enabled by " << i << "\n";
                // }
                // } else{
                bool cond1 = r - l == freq[i][r] - freq[i][l];
                // if(cond1){
                //     cout << "cond1 enabled by " << i << "\n";
                // }
                allsame1 = allsame1 || cond1;
                // }
            }
            bool allsame2 = allsame2e && allsame2o;
            bool wholePal = ha.hashInterval(l, r) == rha.hashInterval(n - r, n - l);
            // cout << wholePal << "\n";
            if(!allsame2){
                // odd case
                ans -= 1;
                ll ind = r - l;
                if(ind % 2 == 0) ind--;
                // cout << "odd case ind: " << ind << "\n";
                ind /= 2;
                ind++;
                ans += ind * ind;
                if((r - l) % 2 == 1 && wholePal) ans -= r - l;
            }
            if(!allsame1){
                // even case
                ll ind = r - l;
                if(ind % 2 == 1) ind--;
                // cout << "even case ind: " << ind << "\n";
                ind /= 2;
                ans += ind * ind + ind;
                if((r - l) % 2 == 0 && wholePal) ans -= r - l;
            }
            cout << ans << "\n";
        }

    }
    
    return 0;
}
