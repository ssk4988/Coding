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

array<vi, 2> manacher(const string& s) {
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
    string s; cin >> s;
    auto m = manacher(s);
    int n = sz(s);
    vi len(n+1);
    rep(i, 0, sz(m[0])) {
        len[i + m[0][i]] = max(len[i + m[0][i]], 2 * m[0][i]);
    }
    rep(i, 0, sz(m[1])) {
        len[i + 1 + m[1][i]] = max(len[i+1+m[1][i]], 2*m[1][i]+1);
    }
    for(int i = n-1; i > 0; i--) {
        len[i] = max(len[i], len[i+1]-2);
    }
    rep(i,1,n+1){
        cout << len[i] << " ";
    }
    cout << "\n";
    
    return 0;
}
