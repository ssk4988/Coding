#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vii = vector<pii>;
using vll = vector<pll>;;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)


struct Eertree {
	vector<int> slink = {0, 0}, len = {-1, 0};
	vector<vector<int>> down;
	int cur = 0, t = 0;
	Eertree(string &str) : down(2, vector<int>(2, -1)) {
		for (int i = 0; i < str.size(); i++) {
			char c = str[i]; int ci = c - '0';
			while (t <= 0 || str[t-1] != c) 
				t = i - len[cur = slink[cur]];
			if (down[cur][ci] == -1) {
				down[cur][ci] = slink.size();
				down.emplace_back(2, -1);
				len.push_back(len[cur] + 2);
				if (len.back() > 1) {
					do t = i - len[cur = slink[cur]];
					while(t <= 0 || str[t-1] != c);
					slink.push_back(down[cur][ci]);
				} else slink.push_back(1);
				cur = slink.size() - 1;
			} else cur = down[cur][ci];
			t = i - len[cur] + 1;
		}
	}
};


int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    string str; cin >> str;
    string v(str);
    rep(i, 1, n){
        if(str[i] == str[i-1]) v[i] = '0' + (1 - (v[i-1] - '0'));
        else v[i] = v[i-1];
    }
    // cout << v << "\n";
    Eertree e(v);
    vl ans(sz(e.slink), 1);
    for(int i = sz(ans) - 1; i >= 1; i--){
        ans[e.slink[i]] += ans[i];
    }
    ll val = 0;
    rep(i, 0, sz(e.slink)){
        if(e.len[i] > 0 && e.len[i] % 2 == 0) val += ans[i];
    }
    cout << val << "\n";

    
    return 0;
}
