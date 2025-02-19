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

struct st {int len, pos, term, link=-1; map<char, int> next;};
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
					a.push_back(a[q]);
					a.back().len = a[p].len + 1;
					for(; p >= 0 && a[p].next[c] == q; p = a[p].link)
						a[p].next[c] = sz(a)-1;
					a[q].link = a[cur].link = sz(a)-1;
				}
			}
		}
		while(last >= 0) a[last].term = 1, last = a[last].link;
        vvi buckets(sz(a));
        rep(u, 0, sz(a)) buckets[a[u].len].push_back(u);
        rep(i, 0, sz(buckets))
            for(int u : buckets[i]) topsort.push_back(u);
	}
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    string str; cin >> str;
    string str2 = str + str;
    SuffixAutomaton sam(str2);
    vi longest(sz(sam.a));
    for(int i = sz(sam.topsort)-1; i >= 0; i--) {
        int u = sam.topsort[i];
        for(auto [c, v] : sam.a[u].next) {
            longest[u] = max(longest[u], 1+longest[v]);
        }
    }
    // auto go = [&](int u, auto &&go) ->int {
    //     if(longest[u] != -1)return longest[u];
    //     longest[u] = 0;
    //     for(auto [c, v] : sam.a[u].next) {
    //         longest[u] = max(longest[u], 1 + go(v, go));
    //     }
    //     return longest[u];
    // };
    int u = 0;
    string ans;
    while(sz(ans) < sz(str)) {
        for(auto [c, v] : sam.a[u].next) {
            if(1 + sz(ans) + longest[v] >= sz(str)) {
                ans += c;
                u = v;
                break;
            }
        }
    }
    cout << ans << "\n";

    return 0;
}
