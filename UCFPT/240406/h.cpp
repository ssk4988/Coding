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
    int nc; cin >> nc;
    rep(cn, 0, nc){
        string a; vector<string> w(2); cin >> a >> w[0] >> w[1];
        vi alpha(26);
        for(char c : a){
            alpha[c - 'a'] = 1;
        }
        vector<vvi> aut(2);
        rep(t, 0, 2){
            vi k = kmp(w[t]);
            rep(i, 0, sz(w[t])+1){
                if(i == 0) aut[t].pb(vi(26));
                else aut[t].pb(aut[t][k[i-1]]);
                if(i < sz(w[t])){
                    aut[t].back()[w[t][i] - 'a'] = i+1;
                }
            }
        }
        using a3 = array<int, 3>;
        vector<vvi> vis(3, vvi(sz(w[0]), vi(sz(w[1]))));
        vis[1][0][0] = true;
        queue<a3> q;
        q.push({1, 0, 0});
        bool inf0 = false, inf1 = false;
        while(!q.empty()){
            auto [dif, u, v] = q.front(); q.pop();
            rep(i, 0, 26){
                if(!alpha[i]) continue;
                int dif1 = dif, u1 = aut[0][u][i], v1 = aut[1][v][i];
                if(u1 == sz(w[0])){
                    u1 = 0, dif1++;
                }
                if(v1 == sz(w[1])){
                    v1 = 0, dif1--;
                }
                if(dif1 < 0 || dif1 >= 3){
                    if(dif1 < 0) inf1 = true;
                    if(dif1 >= 3) inf0 = true;
                    continue;
                }
                if(vis[dif1][u1][v1]) continue;
                vis[dif1][u1][v1] = true;
                q.push({dif1, u1, v1});
            }
        }
        cout << !(inf0 && inf1) << "\n";
    }

    
    return 0;
}