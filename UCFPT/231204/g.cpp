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

// vi pi(const string& s) {
// 	vi p(sz(s));
// 	rep(i,1,sz(s)) {
// 		int g = p[i-1];
// 		while (g && s[i] != s[g]) g = p[g-1];
// 		p[i] = g + (s[i] == s[g]);
// 	}
// 	return p;
// }

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    string str; cin >> str;
    int n = sz(str);
    rep(i, 1, n + 1){
        if(n % i != 0) continue;
        vector<string> ans;
        rep(j, 0, n - i + 1){
            string s1 = str.substr(j, i) + '\0' + str;
            vi p(1), idx(1);
            int g;
            rep(k, 1, sz(s1)){
                for(g = p.back(); g && s1[k] != s1[idx[g]]; g = p[g-1]);
                idx.pb(k);
                p.pb(g + (s1[k] == s1[idx[g]]));
                if(p.back() == i){
                    rep(l, 0, i){
                        // idx.pop_back();
                        // p.pop_back();
                    }
                }
            }
            if(sz(p) == i + 1){
                ans.push_back(str.substr(j, i));
            }
        }
        if(sz(ans)){
            sort(all(ans));
            cout << ans[0] << "\n";
            return 0;
        }
    }
    
    return 0;
}
