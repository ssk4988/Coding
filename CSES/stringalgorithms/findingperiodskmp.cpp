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
    string str; cin >> str;
    vi k = kmp(str);
    vi ans(sz(str) + 1);
    int len = sz(str);
    for(int i = 0; i < sz(k); i++){
        cout << i << " " << k[i] << nL;
    }

    ans[len] = true;
    while(len && k[len-1] * 2 >= len){
        // cout << (sz(str) - len) << nL;
        // ans.pb(sz(str) - len);
        len = k[len-1];
        ans[len] = true;
    }
    // reverse(all(ans));
    for(int i = sz(ans) - 1; i >= 0; i--){
        if(ans[i]){
            for(int j = i; j < sz(ans); j += i) ans[j] = true;
        }
    }
    // ans.pb(sz(str));
    rep(i, 0, sz(ans)){
        if(ans[i]) cout << i << " ";
    }
    cout << nL;
    return 0;
}
