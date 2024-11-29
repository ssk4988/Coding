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
using vll = vector<pll>;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

const ll MOD = 1e9+7;

struct Eertree {
	vi slink = {0, 0}, len = {-1, 0}, diff = {0, 0}, series = {0, 0};
    vi slink2 = {-1, -1};
	vvi down;
	int cur = 0, t = 0;
    vl dp{1}, pdp = {1, 1};
	Eertree(string &str) : down(2, vi(26, -1)) {
		for (int i = 0; i < sz(str); i++) {
			char c = str[i]; int ci = c - 'a';
			while (t <= 0 || str[t-1] != c) 
				t = i - len[cur = slink[cur]];
			if (down[cur][ci] == -1) {
				down[cur][ci] = sz(slink);
				down.emplace_back(26, -1);
				len.push_back(len[cur] + 2);
                pdp.push_back(0);
				if (len.back() > 1) {
					do t = i - len[cur = slink[cur]];
					while(t <= 0 || str[t-1] != c);
					slink.push_back(down[cur][ci]);
				} else slink.push_back(1);
				cur = sz(slink) - 1;

                if(len[cur] == 1) slink2.push_back(1);
                else {
                    slink2.push_back(len[slink[cur]] % 2 == 0 ? slink[cur] : slink2[slink[cur]]);
                }
                diff.push_back(len[cur] - len[slink2[cur]]);
                series.push_back(diff[cur] == diff[slink2[cur]] ? series[slink2[cur]] : slink2[cur]);
			} else cur = down[cur][ci];
			t = i - len[cur] + 1;
            dp.push_back(0);
            if (i % 2 == 0) continue;
            for(int u = cur; len[u] > 0; u = series[u]) {
                // pdp[u] = dp[i+1 - len[series[u]] - diff[u]];
                // if ((len[series[u]] + diff[u])%2 == 0) pdp[0][u] = dp[i+1 - len[series[u]] - diff[u]];
                // rep(t, 0, 2) {
                //     if (series[u] != slink[u]) (pdp[t][u] += pdp[t ^ (diff[u]%2)][slink[u]]) %= MOD;
                // }
                pdp[u] = dp[i+1 - len[series[u]] - diff[u]];
                if (series[u] != slink2[u]) (pdp[u] += pdp[slink2[u]]) %= MOD;
                (dp[i + 1] += pdp[u]) %= MOD;
            }
		}
	}
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    string s; cin >> s;
    string p;
    int n = sz(s);
    rep(i, 0, n){
        if(i > n - 1 - i) break;
        p += s[i];
        p += s[n-1-i];
    }
    Eertree e(p);
    cout << e.dp.back() << "\n";
    
    return 0;
}
