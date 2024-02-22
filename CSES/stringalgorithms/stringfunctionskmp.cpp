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

vi kmp(const string& s) {
	vi p(sz(s));
	rep(i,1,sz(s)) {
		int g = p[i-1];
		while (g && s[i] != s[g]) g = p[g-1];
		p[i] = g + (s[i] == s[g]);
	}
	return p;
}

vi kmpToZ(vi &kmp){
	vi Z(sz(kmp));
	for(int i = 0; i < sz(kmp); i++)
		if(kmp[i])
			Z[i - kmp[i] + 1] = kmp[i];
	for(int i = 0, L = -1, R = -1; i < sz(kmp); i++){
		if(Z[i]){
			if(i + Z[i] > R) R = i + Z[i], L = i;
		} else if(i < R)
			Z[i] = min(R - i, Z[i - L]);
	}
	return Z;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    string str; cin >> str;
    vi k = kmp(str), z = kmpToZ(k);
    rep(i, 0, sz(z)) cout << z[i] << " ";
    cout << nL;
    rep(i, 0, sz(k)) cout << k[i] << " ";
    cout << nL;
    
    return 0;
}
