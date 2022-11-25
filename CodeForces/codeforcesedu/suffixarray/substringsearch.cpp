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

typedef pair<ll, int> pli;
void count_sort(vector<pli> &b, int bits) { // (optional)
	//this is just 3 times faster than stl sort for N=10^6
	int mask = (1 << bits) - 1;
	rep(it,0,2) {
		int move = it * bits;
		vi q(1 << bits), w(sz(q) + 1);
		rep(i,0,sz(b))
			q[(b[i].first >> move) & mask]++;
		partial_sum(q.begin(), q.end(), w.begin() + 1);
		vector<pli> res(b.size());
		rep(i,0,sz(b))
			res[w[(b[i].first >> move) & mask]++] = b[i];
		swap(b, res);
	}
}
struct SuffixArray {
	vi a;
	string s;
	SuffixArray(const string& _s) : s(_s + '\0') {
		int N = sz(s);
		vector<pli> b(N);
		a.resize(N);
		rep(i,0,N) {
			b[i].first = s[i];
			b[i].second = i;
		}

		int q = 8;
		while ((1 << q) < N) q++;
		for (int moc = 0;; moc++) {
			count_sort(b, q); // sort(all(b)) can be used as well
			a[b[0].second] = 0;
			rep(i,1,N)
				a[b[i].second] = a[b[i - 1].second] +
					(b[i - 1].first != b[i].first);

			if ((1 << moc) >= N) break;
			rep(i,0,N) {
				b[i].first = (ll)a[i] << q;
				if (i + (1 << moc) < N)
					b[i].first += a[i + (1 << moc)];
				b[i].second = i;
			}
		}
		rep(i,0,sz(a)) a[i] = b[i].second;
	}
	vi lcp() {
		// longest common prefixes: res[i] = lcp(a[i], a[i-1])
		int n = sz(a), h = 0;
		vi inv(n), res(n);
		rep(i,0,n) inv[a[i]] = i;
		rep(i,0,n) if (inv[i] > 0) {
			int p0 = a[inv[i] - 1];
			while (s[i + h] == s[p0 + h]) h++;
			res[inv[i]] = h;
			if(h > 0) h--;
		}
		return res;
	}
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    string str;
    cin >> str;

    SuffixArray sa = SuffixArray(str);
    int n; cin >> n;
    rep(i, 0, n){
        string c; cin >> c;
        int lo = 0;
        int hi = str.length();
        while(lo < hi){
            int mid = lo + (hi - lo + 1) / 2;
            if(c.compare(str.substr(sa.a[mid], c.length())) >= 0){
                lo = mid;
            }
            else{
                hi = mid - 1;
            }
        }
        // cout << lo << str.substr(sa.a[lo], c.length()) << " " << str.substr(sa.a[lo], 1000) << nL;
        if(c.compare(str.substr(sa.a[lo], c.length())) == 0){
            cout << "Yes\n";
        }
        else{
            cout << "No\n";
        }
    }
    return 0;
}