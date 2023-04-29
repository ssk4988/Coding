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

struct Line {
	mutable double k, m, p;
	bool operator<(const Line& o) const { return k < o.k; }
	bool operator<(double x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
	// (for doubles, use inf = 1/.0, div(a,b) = a/b)
	 const double inf = 1/.0;
	double div(double a, double b) { // floored division
		return a / b; }
	bool isect(iterator x, iterator y) {
		if (y == end()) return x->p = inf, 0;
		if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
		else x->p = div(y->m - x->m, x->k - y->k);
		return x->p >= y->p;
	}
	void add(double k, double m) {
        k *= -1, m *= -1;
		auto z = insert({k, m, 0}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p)
			isect(x, erase(y));
	}
	double query(double x) {
		assert(!empty());
		auto l = *lower_bound(x);
		return -(l.k * x + l.m);
	}
};

const int maxN = 2e5+10, maxK = 55;
// double dp[maxK][maxN];
double dp[maxK][2];
double t[maxN], preft[maxN], prefpt[maxN], pref1t[maxN];

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, k; cin >> n >> k;
    rep(i, 0, n){
        cin >> t[i];
        preft[i + 1] = t[i];
        pref1t[i + 1] = 1 / double(t[i]);
        preft[i + 1] += preft[i];
        pref1t[i + 1] += pref1t[i];
        prefpt[i+1] = preft[i+1] / t[i];
        prefpt[i +1] += prefpt[i];
    }
    dp[0][0] = 0;
    vector<LineContainer> lcs(k + 1);
    lcs[0].add(-preft[0], 0 - prefpt[1] + preft[0] * pref1t[1]);
    rep(j, 1, n+1){
        for(int i = k; i > 0; i--){
            if(lcs[i - 1].size() == 0) continue;
            dp[i][1] = prefpt[j] + 1 + lcs[i - 1].query(pref1t[j]);
            // cout << "for i=" << i << " and j=" << j << " added line k=" << (-preft[j]) << " and m=" << (dp[i][j] - prefpt[j + 1] + preft[j] * pref1t[j + 1]) << nL;
            lcs[i].add(-preft[j], dp[i][1] - prefpt[j + 1] + preft[j] * pref1t[j + 1]);
        }
        for(int i = k; i >= 0; i--){
            dp[i][0] = dp[i][1];
        }
    }
    cout << fixed << setprecision(8) << dp[k][1] << nL;

    
    return 0;
}