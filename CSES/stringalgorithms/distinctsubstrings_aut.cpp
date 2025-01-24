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

struct st { int len, pos, term; st *link; map<char, st*> next; int seen = 0; };
st *suffixAutomaton(string &str) {
	st *last = new st(), *root = last;
	for(auto c : str) {
		st *p = last, *cur = last = new st{p->len + 1, p->len};
		while(p && !p->next.count(c))
			p->next[c] = cur, p = p->link;
		if (!p) cur->link = root;
		else {
			st *q = p->next[c];
			if (p->len + 1 == q->len) cur->link = q;
			else {
				st *clone = new st{p->len+1, q->pos, 0, q->link, q->next};
				for (; p && p->next[c] == q; p = p->link)
					p->next[c] = clone;
				q->link = cur->link = clone;
			}
		}
	}
	while(last) last->term = 1, last = last->link;
	return root;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    string str; cin >> str;
    st *root = suffixAutomaton(str);
	ll ans = 0;
	auto dfs = [&](st *cur, auto &&dfs) -> void {
		if(cur->seen) return;
		ans += cur->len;
		if(cur->link) {
			ans -= cur->link->len;
		}
		cur->seen = 1;
		for(auto [key, val] : cur->next) {
			dfs(val, dfs);
		}
	};
    dfs(root, dfs);
	// ans--;
    cout << ans << "\n";
    
    return 0;
}
