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

struct Eertree {
	vi slink = {0, 0}, len = {-1, 0}, ends{-1, -1};
    vector<map<int, int>> down;
	int cur = 0, t = 0;
    vi at;
    vvi jmp;
	Eertree(vi &str) : down(2) {
		for (int i = 0; i < sz(str); i++) {
			int c = str[i]; int ci = c;
			while (t <= 0 || str[t-1] != c) 
				t = i - len[cur = slink[cur]];
			if (!down[cur].count(ci)) {
				down[cur][ci] = sz(slink);
                down.push_back({});
				len.push_back(len[cur] + 2);
                ends.push_back(i);
				if (len.back() > 1) {
					do t = i - len[cur = slink[cur]];
					while(t <= 0 || str[t-1] != c);
					slink.push_back(down[cur][ci]);
				} else slink.push_back(1);
				cur = sz(slink) - 1;
			} else cur = down[cur][ci];
			t = i - len[cur] + 1;
            at.push_back(cur);
		}
        jmp = vector(20, slink);
        for(int i = 0; i+1 < 20; i++) {
            rep(j, 0, sz(jmp[i])) {
                jmp[i+1][j] = jmp[i][jmp[i][j]];
            }
        }
	}
};

/*
abbacabbac

*/

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, q; cin >> n >> q;
    vi a(n);
    rep(i, 0, n) {
        cin >> a[i];
    }
    vi c(a);
    sort(all(c));
    c.erase(unique(all(c)), end(c));
    rep(i, 0, n) a[i] = lower_bound(all(c), a[i])-c.begin();
    Eertree e(a);
    vi lis, pref{0};
    vii st;
    auto push = [&](int v) -> void {
        auto it = upper_bound(all(lis), v);
        if(it == end(lis)) {
            lis.push_back(1);
            it = prev(end(lis));
        }
        st.push_back({it-begin(lis), *it});
        *it = v;
        pref.push_back(sz(lis));
    };
    auto pop = [&]() -> void {
        pref.pop_back();
        auto [i, v] = st.back();
        st.pop_back();
        if(v == 1) lis.pop_back();
        else lis[i] = v;
    };
    vi ans(sz(e.len), -1);
    auto dfs = [&](int u, auto &&dfs) -> void {
        // if(e.len[u] % 2 == 0) {
            // cerr << "ans is " << ans[u] << endl;
            // }
        ans[u] = pref.back();
        // cerr << "dfs at " << u << " " << ans[u] << endl;
        // for(int v : pref) cerr << v << " ";
        // cerr << endl;
        for(auto [_, v] : e.down[u]) {
            if (e.len[v] != 2 + e.len[u] || ans[v] != -1) continue;
            // cerr << "trans from " << u << " to " << v << endl;
            push(-a[e.ends[v]]);    
            dfs(v, dfs);
            pop();
        }
    };
    dfs(1, dfs);
    rep(qid, 0, q) {
        int l, r; cin >> l >> r; l--, r--;
        int u = e.at[r];
        for(int p = 20-1; p >= 0; p--) {
            if(e.len[e.jmp[p][u]] >= r-l+1) u = e.jmp[p][u];
        }
        if(e.len[u] != r-l+1) {
            cout << "-1\n";
        }
        else cout << (r-l+1)/2-ans[u] << "\n";
    }


    return 0;
}
