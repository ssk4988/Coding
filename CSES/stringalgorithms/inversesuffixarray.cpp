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


struct SuffixArray {
	vi sa, lcp;
	SuffixArray(vector<char> s, int lim=256) { // or vector<int>
		s.push_back(0); int n = sz(s), k = 0, a, b;
		vi x(all(s)), y(n), ws(max(n, lim));
		sa = lcp = y, iota(all(sa), 0);
		for (int j = 0, p = 0; p < n; j = max(1, j * 2), lim = p) {
			p = j, iota(all(y), n - j);
			rep(i,0,n) if (sa[i] >= j) y[p++] = sa[i] - j;
			fill(all(ws), 0);
			rep(i,0,n) ws[x[i]]++;
			rep(i,1,lim) ws[i] += ws[i - 1];
			for (int i = n; i--;) sa[--ws[x[y[i]]]] = y[i];
			swap(x, y), p = 1, x[sa[0]] = 0;
			rep(i,1,n) a = sa[i - 1], b = sa[i], x[b] =
				(y[a] == y[b] && y[a + j] == y[b + j]) ? p - 1 : p++;
		}
		for (int i = 0, j; i < n - 1; lcp[x[i++]] = k)
			for (k && k--, j = sa[x[i] - 1];
					s[i + k] == s[j + k]; k++);
	}
};
// when comparing a and b (a is before b in suffix array)
// compare a+1 and b+1. if a+1 after b+1, then char(a) < char(b)
// is it ok to let them be the same otherwise?


int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vi p(n), inv(n);
    rep(i, 0, n) {
        cin >> p[i]; p[i]--;
        inv[p[i]] = i;
    }
    vector<char> s(n, 'a');
    char cur = 'a';
    s[p[0]] = cur;
    rep(i, 0, n-1) {
        int a = p[i], b = p[i+1];
        if(a == n-1) {
            // no conclusion
        }
        else if(b == n-1 || inv[b+1] < inv[a+1]) {
            cur++;
            if(cur > 'z') {
                cout << "-1\n";
                return 0;
            }
        }
        s[b] = cur;
    }
    for(char c : s) cout << c;
    cout << "\n";
    
    return 0;
}
