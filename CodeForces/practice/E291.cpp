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
    int n; cin >> n;
    vector<vector<pair<int, string>>> adj(n);
    rep(i, 1, n){
        int p; cin >> p; p--;
        string str; cin >> str;
        adj[p].pb({i, str});
    }
    string t; cin >> t;
    vi kp = kmp(t);
    vvi aut(sz(t)+1, vi(26));
    aut[0][t[0] - 'a'] = 1;
    rep(i, 1, sz(aut)){
        aut[i] = aut[kp[i-1]];
        if(i < sz(t)){
            aut[i][t[i] - 'a'] = i+1;
        }
    }
    ll ans = 0;
    auto dfs = [&](int u, int len, auto &&dfs) -> void {
        for(auto [v, str] : adj[u]){
            int len1 = len;
            for(char c : str){
                len1 = aut[len1][c - 'a'];
                if(len1 == sz(t)){
                    ans++;
                }
            }
            dfs(v, len1, dfs);
        }
    };
    dfs(0, 0, dfs);
    cout << ans << "\n";

    return 0;
}