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

vi Z(const string& S) {
	vi z(sz(S));
	int l = -1, r = -1;
	rep(i,1,sz(S)) {
		z[i] = i >= r ? 0 : min(r - i, z[i - l]);
		while (i + z[i] < sz(S) && S[i + z[i]] == S[z[i]])
			z[i]++;
		if (i + z[i] > r)
			l = i, r = i + z[i];
	}
	return z;
}

vi ZtoKMP(vi &Z) {
	vi p(sz(Z));
	for(int i = sz(Z) - 1; i >= 0; i--)
		if(Z[i]) p[i + Z[i] - 1] = Z[i];
	for(int i = sz(Z) - 2; i >= 0; i--)
		p[i] = max(p[i], p[i + 1] - 1);
	
	return p;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    string str; cin >> str;
    vi z = Z(str), k = ZtoKMP(z);
    rep(i, 0, sz(z)) cout << z[i] << " ";
    cout << nL;
    rep(i, 0, sz(k)) cout << k[i] << " ";
    cout << nL;
    
    return 0;
}
