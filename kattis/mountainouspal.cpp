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

array<vi, 2> manacher(const vi& s) {
	int n = sz(s);
	array<vi,2> p = {vi(n+1), vi(n)};
	rep(z,0,2) for (int i=0,l=0,r=0; i < n; i++) {
		int t = r-i+!z;
		if (i<r) p[z][i] = min(t, p[z][l+t]);
		int L = i-p[z][i], R = i+p[z][i]-!z;
		while (L>=1 && R+1<n && s[L-1] == s[R+1])
			p[z][i]++, L--, R++;
		if (R>r) l=L, r=R;
	}
	return p;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vi a(n);
    rep(i, 0, n) cin >> a[i];
    auto pal = manacher(a);
    vi inc(n);
    vi best(n);
    for(int i = n-2; i >= 0; i--) {
        if(a[i] < a[i+1]) inc[i] = inc[i+1]+1;
        best[i + inc[i]] = max(best[i + inc[i]], inc[i]);
    }
    int ans = -1;
    rep(i, 0, sz(pal[1])) {
        int l = min(best[i], pal[1][i]);
        if(l * 2 + 1 >= 3) {
            ans = max(ans, 2 * l + 1);
        }
    }
    cout << ans << "\n";
    
    return 0;
}
