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

struct st { int len, pos, term, link=-1; map<char, int> next; 
    // int endpos; ll to, from=1; 
};
struct SuffixAutomaton {
	vector<st> a;
	SuffixAutomaton(string &str) {
		a.resize(1);
		int last = 0;
		for(auto c : str) {
			int p = last, cur = last = sz(a);
			a.push_back({a[p].len + 1, a[p].len});
			while(p >= 0 && !a[p].next.count(c))
				a[p].next[c] = cur, p = a[p].link;
			if (p == -1) a[cur].link = 0;
			else {
				int q = a[p].next[c];
				if (a[p].len + 1 == a[q].len) a[cur].link = q;
				else {
					a.push_back(a[q]);
					a.back().len = a[p].len+1;
					for(; p >= 0 && a[p].next[c] == q; p = a[p].link)
						a[p].next[c] = sz(a)-1;
					a[q].link = a[cur].link = sz(a)-1;
				}
			}
            // a[last].endpos++;
		}
		while(last >= 0) a[last].term = 1, last = a[last].link;
        // calcExtra();
	}
    // vi topnext, toplink;
    // vvi suffadj;
    // void calcExtra() {
    //     suffadj.resize(sz(a));
    //     rep(u, 1, sz(a)) suffadj[a[u].link].push_back(u);
    //     vi seen(sz(a));
    //     auto dfs = [&](int u, auto &&dfs) {
    //         if(seen[u]) return;
    //         seen[u] = true;
    //         for(auto [c, v] : a[u].next)
    //             dfs(v, dfs), a[u].from += a[v].from;
    //         topnext.push_back(u);
    //     };
    //     dfs(0, dfs);
    //     seen = vi(sz(a));
    //     auto dfs1 = [&](int u, auto &&dfs1) {
    //         if(seen[u]) return;
    //         seen[u] = true;
    //         for(int v : suffadj[u]) dfs1(v, dfs1);
    //         toplink.push_back(u);
    //     };
    //     dfs1(0, dfs1);
    //     rep(i, 0, sz(a)-1) 
    //         a[a[toplink[i]].link].endpos += a[toplink[i]].endpos;
    //     reverse(all(topnext)), reverse(all(toplink));
    //     a[0].to = 1;
    //     for(int u : topnext)
    //         for(auto [c, v] : a[u].next)
    //             a[v].to += a[u].to;
    // }
};


int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    string str; cin >> str;
	SuffixAutomaton sa(str);
	vi seen(sz(sa.a));
	ll ans = 0;
	auto dfs = [&](int u, auto &&dfs) -> void {
		if(seen[u]) return;
		seen[u] = 1;
		ans += sa.a[u].len;
		if(sa.a[u].link >= 0) {
			ans -= sa.a[sa.a[u].link].len;
		}
		for(auto [key, val] : sa.a[u].next) {
			dfs(val, dfs);
		}
	};
	dfs(0, dfs);
    cout << ans << "\n";
    
    return 0;
}
