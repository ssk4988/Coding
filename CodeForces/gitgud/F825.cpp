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
    int n = sz(str);
    vi dp(n+1, 1e9);
    dp[0] = 0;
    vi memotimes(n + 1, -1);
    memotimes[0] = 0;
    auto digs = [&](int times) -> int {
        int &cnt = memotimes[times];
        if(cnt != -1) return cnt;
        cnt = 0;
        while(times){times /= 10; cnt++; }
        return cnt;
    };
    rep(start, 0, n){
        string s = str.substr(start);
        vi p = kmp(s);
        rep(i, 0, sz(p)){
            if((i+1) % (i+1 - p[i]) == 0){
                int times = (i+1) / (i+1 - p[i]);
                int per = i+1-p[i];
                dp[start + i + 1] = min(dp[start + i + 1], dp[start] + per + digs(times));
                // rep(j, 1, times + 1){
                //     dp[start + j * per] = min(dp[start + j * per], dp[start] + per + digs(j));
                // }
            }
            dp[start + i + 1] = min(dp[start + i + 1], dp[start] + i + 1 + digs(1));
        }
    }
    cout << dp[n] << "\n";
    
    return 0;
}
