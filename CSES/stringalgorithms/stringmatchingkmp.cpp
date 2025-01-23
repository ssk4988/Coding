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

vector<int> kmp(const string& s) {
	vector<int> pi(sz(s));
	for (int i = 1; i < sz(s); i++) {
		pi[i] = pi[i-1];
		while (pi[i] && s[i] != s[pi[i]]) pi[i] = pi[pi[i]-1];
		if (s[i] == s[pi[i]]) pi[i]++;
	}
	return pi;
}

vector<int> match(const string& s, const string& pat) {
	vector<int> p = kmp(pat + '\0' + s), res;
	for (int i = sz(p)-sz(s); i < sz(p); i++)
		if (p[i] == sz(pat)) res.push_back(i - 2 * sz(pat));
	return res;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    string str, p;
    cin >> str >> p;
    cout << sz(match(str, p)) << "\n";

    return 0;
}
