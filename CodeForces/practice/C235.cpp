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

struct st {int len, pos, term, link=-1; map<char, int> next;
    int endpos; ll to, from = 1; // add to end of st
};
struct SuffixAutomaton {
	vector<st> a;
    vi topsort;
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
                    a.push_back({a[p].len+1, a[q].pos, 0, a[q].link, a[q].next});
					for(; p >= 0 && a[p].next[c] == q; p = a[p].link)
						a[p].next[c] = sz(a)-1;
					a[q].link = a[cur].link = sz(a)-1;
				}
			}
            a[last].endpos++;
		}
		while(last >= 0) a[last].term = 1, last = a[last].link;
        vvi buckets(sz(a));
        rep(u, 0, sz(a)) buckets[a[u].len].push_back(u);
        rep(i, 0, sz(buckets))
            for(int u : buckets[i]) topsort.push_back(u);
        for(int i = sz(a)-1; i >= 0; i--) {
            int u = topsort[i];
            for(auto [c, v] : a[u].next)
                a[u].from += a[v].from;
            if(u) a[a[u].link].endpos += a[u].endpos;
        }
        a[0].to = 1;
        for(int u : topsort)
            for(auto [c, v] : a[u].next)
                a[v].to += a[u].to;
	}
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    string s; cin >> s;
    SuffixAutomaton sa(s);
    int q; cin >> q;
    rep(qid, 0, q) {
        string t; cin >> t;
        string t2 = t + t;
        int len = 0, p = 0;
        set<int> seen;
        ll ans = 0;
        for(char c : t2) {
            while(p > 0 && !sa.a[p].next.count(c)) {
                p = sa.a[p].link;
                len = sa.a[p].len;
            }
            if(sa.a[p].next.count(c)){
                len++;
                p = sa.a[p].next[c];
            }
            while(len > sz(t)) {
                len--;
                if(len == sa.a[sa.a[p].link].len) p = sa.a[p].link;
            }
            if(len == sz(t) && !seen.count(p)) {
                seen.insert(p);
                ans += sa.a[p].endpos;
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}
