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

#define maxN 400005
vi sa;
vi lcp;
vi rev;
int st[28][maxN];
int lg[maxN + 1];

int minq(int l, int r)
{
    if(l > r) return 0;
    int i = lg[r - l + 1];
    if(i < 0 || i >= 28 || r - l + 1 > maxN) return 0;
    if(r - (1 << i) + 1 < 0 || r - (1 << i) + 1 >= maxN || l < 0 || l >= maxN) return 0;
    return min(st[i][l], st[i][r - (1 << i) + 1]);
}

bool cmp(pi a, pi b)
{
    if(a.f == b.f) return a.s <= b.s;
    if(a.f < 0 || a.f >= rev.size() || b.f < 0 || b.f >= rev.size()) return true;
    int ls = min(rev[a.f], rev[b.f]);
    int us = max(rev[a.f], rev[b.f]);
    int k = minq(ls + 1, us);
    if(k == 0 || (k > 0 && (b.s - b.f + 1) > k && (a.s - a.f + 1) > k)){
        return rev[a.f] <= rev[b.f];
    }
    if((b.s - b.f + 1) == (a.s - a.f + 1)){
        return a.s <= b.s;
    }
    return (a.s - a.f + 1) <= (b.s - b.f + 1); 
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    string str;
    cin >> str;
    int n = str.size() + 1;
    SuffixArray sao = SuffixArray(str);
    sa = sao.a;
    rev = vi(sa.size());
    lcp = sao.lcp();
    rep(i, 0, sa.size())
    {
        rev[sa[i]] = i;
        st[0][i] = lcp[i];
    }
    lg[1] = 0;
    for (int i = 2; i <= maxN; i++)
        lg[i] = lg[i / 2] + 1;
    rep(i, 1, lg[n] + 1)
    {
        int upb = n - (1 << i) + 1;
        rep(j, 0, upb)
        {
            if(j + (1 << i) > n) continue;
            st[i][j] = min(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
        }
    }
    vpi substrs;
    int q;
    cin >> q;
    rep(i, 0, q)
    {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        substrs.pb({a, b});
    }
    sort(all(substrs), cmp);
    rep(i, 0, q)
    {
        cout << substrs[i].f + 1 << " " << substrs[i].s + 1 << nL;
    }

    return 0;
}