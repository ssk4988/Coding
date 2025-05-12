#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vl = vector<ll>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()

struct st { int len, pos, term, link=-1; map<char, int> next; 
    int endpos; ll to, from=1; };
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
					a.push_back({a[p].len+1, a[q].pos, 0, a[q].link, a[q].next});
					for(; p >= 0 && a[p].next[c] == q; p = a[p].link)
						a[p].next[c] = sz(a)-1;
					a[q].link = a[cur].link = sz(a)-1;
				}
			}
            a[last].endpos++;
		}
		while(last >= 0) a[last].term = 1, last = a[last].link;
        calcExtra();
	}
    vi topsort;
    void calcExtra() {
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

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    string s; cin >> s;
    SuffixAutomaton sa(s);
    int n = sz(sa.a);
    map<char, ll> ans;
    
    rep(u, 0, n) {
        if(u != 0 && sa.a[u].endpos != 0) {
            ll freq = sa.a[u].endpos;
            for(char c : to_string(freq)) {
                ans[c] += sa.a[u].to;
            }
        }
        for(auto [c, v] : sa.a[u].next) {
            ans[c] += sa.a[u].to * sa.a[v].from;
        }
    }
    for(auto [key, val] : ans){
        cout << key << " " << val << "\n";
    }
    return 0;
}
