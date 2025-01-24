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

struct st { int len, pos, clone, term, link=-1; map<char, int> next; int endpos;};
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
					a.push_back(st{a[p].len+1, a[q].pos, 1, 0, a[q].link, a[q].next});
					for(; p >= 0 && a[p].next[c] == q; p = a[p].link)
						a[p].next[c] = clone;
					a[q].link = a[cur].link = clone;
				}
			}
            a[cur].endpos++;
		}
		while(last >= 0) a[last].term = 1, last = a[last].link;
	}
};

// struct st { int len, pos, term; st *link; map<char, st*> next; 
//     ll endpos=0; 
//     ll pathsTo = 0;
//     ll pathsFrom = 0;
// };
// st *suffixAutomaton(string &str) {
//     st *last = new st(), *root = last;
//     for(auto c : str) {
//         st *p = last, *cur = last = new st{last->len + 1, last->len};
//         while(p && !p -> next.count(c))
//             p->next[c] = cur, p = p->link;
//         if(!p) cur->link = root;
//         else {
//             st *q = p->next[c];
//             if(p->len + 1 == q->len) cur->link = q;
//             else {
//                 st* clone = new st{p->len+1, q->pos, 0, q->link, q->next};
//                 for(; p && p->next[c] == q; p = p->link)
//                     p->next[c] = clone;
//                 q->link = cur->link = clone;
//             }
//         }
//         last->endpos++;
//     }
//     while(last) last->term = 1, last = last->link;
//     return root;
// }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    string s; cin >> s;
    SuffixAutomaton sa(s);
    int n = sz(sa.a);
    vl pathsFrom(n, 1), pathsTo(n);
    vvi adj(n);
    pathsTo[0] = 1;
    vi ts;
    vi seen(n);
    map<char, int> ans;
    auto dfs = [&](int u, auto &&dfs) -> void {
        if(seen[u]) return;
        seen[u] = true;
        if(u) {
            adj[sa.a[u].link].push_back(u);
        }
        for(auto [key, val] : sa.a[u].next) {
            dfs(val, dfs);
            pathsFrom[u] += pathsFrom[val];
        }
        ts.push_back(u);
    };
    dfs(0, dfs);
    reverse(all(ts));
    for(int i = n-1; i > 0; i--) {
        sa.a[sa.a[ts[i]].link].endpos += sa.a[ts[i]].endpos;
    }
    for(int u : ts) {
        for(auto [key, val] : sa.a[u].next) {
            pathsTo[val] += pathsTo[u];
        }
    }
    for(auto u : ts) {
        if(u != 0 && sa.a[u].endpos != 0) {
            ll freq = sa.a[u].endpos;
            for(char c : to_string(freq)) {
                ans[c] += pathsTo[u];
            }
        }
        for(auto [key, val] : sa.a[u].next) {
            ans[key] += pathsTo[u] * pathsFrom[val];
        }
    }
    // for(auto u : ts){
    //     cerr << get_idx[u] << " " << u->endpos << " " << u->pathsFrom << " " << u->pathsTo << endl;
    // }
    for(auto [key, val] : ans){
        cout << key << " " << val << "\n";
    }
    return 0;
}
