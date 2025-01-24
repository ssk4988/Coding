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

vi duval(string &s) {
	vi ans;
	for(int start = 0; start < sz(s);) {
		int i = start+1, j = start;
		for(; i < sz(s) && s[i] >= s[j]; i++)
			if(s[i] > s[j]) j = start;
			else j++;
		for(int sz = i-j; start + sz <= i; start += sz)
			ans.push_back(start);
	}
	return ans;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    string s; cin >> s;
    vi f = duval(s);
    f.push_back(sz(s));
    for(int i : f) cout << i << " ";
    cout << "\n";
    
    return 0;
}
