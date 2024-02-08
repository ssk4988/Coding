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

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    string str; int d; cin >> str >> d;
    int n = sz(str);
    vi kmp(n);
    int ans = 0;
    int start = 0;
    while(start < n){
        int i;
        for(i = start + 1; i < n; i++){
            int g = kmp[i-1];
            while (g && str[i] != str[start + g]) g = kmp[g-1];
            kmp[i] = g + (str[i] == str[start + g]);
            if(i - start >= d && i - kmp[i] + 1 > i) break;
        }
        // cout << "start " << start << " end " << i << nL;
        start = i;
        ans++;
    }
    cout << ans << nL;
    
    return 0;
}
