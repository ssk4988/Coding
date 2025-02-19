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
    array<int, 3> endpos{0, 0, 0}; ll to, from = 1; // add to end of st
};
struct SuffixAutomaton {
	vector<st> a;
    vi topsort;
	SuffixAutomaton(string &str, vi starts, vi ends) {
		a.resize(1);
		int last = 0;
        int idx = 0;
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
            int v = -1;
            rep(i, 0, 3) if(starts[i] <= idx && idx < ends[i]) v = i;
            if(v != -1) a[last].endpos[v]++;
            idx++;
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
            if(u) 
                rep(j, 0, 3)
                    a[a[u].link].endpos[j] += a[u].endpos[j];
        }
        a[0].to = 1;
        for(int u : topsort)
            for(auto [c, v] : a[u].next)
                a[v].to += a[u].to;
	}
};
const int mod = 1e9+7;
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    string a, b, c; cin >> a >> b >> c;
    string s = a + char(0) + b + char(1) + c + char(2);
    vi starts{0, sz(a)+1, sz(a) + sz(b) + 2};
    vi ends{starts[1]-1, starts[2]-1, sz(s)};
    SuffixAutomaton sa(s, starts, ends);
    vl ans(sz(s)+3);
    rep(i, 1, sz(sa.a)) {
        ll v = ll(sa.a[i].endpos[0]) * sa.a[i].endpos[1] * sa.a[i].endpos[2] % mod;
        (ans[sa.a[sa.a[i].link].len+1] += v) %= mod;
        (ans[sa.a[i].len+1] += mod-v) %= mod;
    }
    rep(i, 1, 1+min({sz(a), sz(b), sz(c)})) {
        (ans[i] += ans[i-1]) %= mod;
        cout << ans[i] << " ";
    }
    cout << "\n";
    
    return 0;
}
