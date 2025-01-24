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

struct st { int len, pos, term, link=-1; map<char, int> next; };
struct SuffixAutomaton {
	vector<st> a;
	SuffixAutomaton(string &str) {
		a.push_back(st());
		int last = 0, root = 0;
		for(auto c : str) {
			int p = last, cur = last = sz(a);
			a.push_back(st{a[p].len + 1, a[p].len});
			while(p >= 0 && !a[p].next.count(c))
				a[p].next[c] = cur, p = a[p].link;
			if (p == -1) a[cur].link = root;
			else {
				int q = a[p].next[c];
				if (a[p].len + 1 == a[q].len) a[cur].link = q;
				else {
					int clone = sz(a);
					a.push_back(st{a[p].len+1, a[q].pos, 0, a[q].link, a[q].next});
					for(; p >= 0 && a[p].next[c] == q; p = a[p].link)
						a[p].next[c] = clone;
					a[q].link = a[cur].link = clone;
				}
			}
		}
		while(last >= 0) a[last].term = 1, last = a[last].link;
	}
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
