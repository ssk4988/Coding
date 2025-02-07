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

#define pb push_back
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

struct st {int len, pos, term, link=-1;
    vi next, linknext;
    ll pathsFrom = -1,  // paths from this node to later in DAG
    linkPaths = -1; // paths from all lengths in suffix links to later in DAG
};
struct SuffixAutomaton {
	vector<st> a;
	SuffixAutomaton(string &str) {
		a.resize(1);
        a.back().linknext = a.back().next = vi(26, -1);
		int last = 0;
		for(auto c1 : str) {
            int c = c1 - 'a';
			int p = last, cur = last = sz(a);
			a.push_back({a[p].len + 1, a[p].len});
            a.back().linknext = a.back().next = vi(26, -1);
			while(p >= 0 && a[p].next[c] == -1)
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
        int n = sz(a);
        vvi adj(n);
        rep(i, 1, n) {
            adj[a[i].link].pb(i);
        }
        auto pathdfs = [&](int u, auto &&pathdfs) -> ll {
            if(a[u].pathsFrom != -1) return a[u].pathsFrom;
            a[u].pathsFrom = (u != 0);
            rep(ch, 0, 26) {
                if(a[u].next[ch] == -1) continue;
                int v = a[u].next[ch];
                a[u].pathsFrom += pathdfs(v, pathdfs);
            }
            return a[u].pathsFrom;
        };
        ll totNonempty = pathdfs(0, pathdfs);
        auto linkdfs = [&](int u, int p, auto &&linkdfs) -> void {
            a[u].linkPaths = 0;
            if(p != -1) {
                int linklen = a[p].len;
                if(p > 0) linklen -= a[a[p].link].len;
                a[u].linkPaths = a[p].linkPaths + a[p].pathsFrom * linklen;
                a[u].linknext = a[p].linknext;
            }
            rep(ch, 0, 26) {
                if(a[u].next[ch] == -1) continue;
                a[u].linknext[ch] = u;
            }
            for(int v : adj[u]) {
                linkdfs(v, u, linkdfs);
            }
        };
        linkdfs(0, -1, linkdfs);
	}
};

// window information:
// string, length of current string, longest prefix in s, longest suffix in t
// number of ways to make this string itself is maxsuff - minsuff + 1
// maxsuff = min(suff, len-1)
// minsuff = max(1, len - pref) (pref must be > 0)
// longest prefix and longest suffix sum must be at least length
// precomp for automaton of t given node and length, number of paths among all suffixes up to that length
// if len is 1, ways to make string is 0 by default
// len 1 - maxsuff and minsuff = 0


string solve(string s, string t, ll k) {
    SuffixAutomaton sa(s), ta(t);

    // if pref is 0, addchar only called with valid char
    auto addchar = [&](char c1, int len, int pref, int prefp, int maxsuff, int maxsuffp, int minsuff, int minsuffp) {
        // w += c;
        int c = c1 - 'a';
        if(pref == len && sa.a[prefp].next[c] != -1) {
            pref++;
            prefp = sa.a[prefp].next[c];
        }

        len++;
        if(len > 1) {
            if(ta.a[maxsuffp].linknext[c] != -1) {
                int msp = ta.a[maxsuffp].linknext[c];
                if(msp != maxsuffp) maxsuff = ta.a[msp].len;
                maxsuffp = msp;
            } else maxsuffp = maxsuff = 0;
            if(ta.a[maxsuffp].next[c] != -1) {
                maxsuffp = ta.a[maxsuffp].next[c];
                maxsuff++;
            }

            if(ta.a[minsuffp].linknext[c] != -1) {
                int msp = ta.a[minsuffp].linknext[c];
                if(msp != minsuffp) minsuff = ta.a[msp].len;
                minsuffp = msp;
            } else minsuffp = minsuff = 0;
            if(ta.a[minsuffp].next[c] != -1) {
                minsuffp = ta.a[minsuffp].next[c];
                minsuff++;
            }

            int iter = 0;
            while(pref + minsuff > len && minsuff > 1) {
                iter++;
                assert(minsuffp > 0 && iter < 3); // cant be root
                if(minsuff-1 == ta.a[ta.a[minsuffp].link].len) {
                    minsuffp = ta.a[minsuffp].link;    
                }
                minsuff--;
            }
        }
        ll curways = 0, pathways = 0;
        if(pref == 0 || pref + maxsuff < len) {
            return tuple{len, pref, prefp, maxsuff, maxsuffp, minsuff, minsuffp, curways, pathways};
        }
        if(len == 1) {
            assert(maxsuffp == 0 && minsuffp == 0 && maxsuff == 0 && minsuff == 0);
            curways = 0;
        } else if(maxsuffp == 0) {}
        else {
            curways = maxsuff - minsuff + 1;
            pathways += ta.a[maxsuffp].linkPaths;
            pathways += ta.a[maxsuffp].pathsFrom * (maxsuff - ta.a[ta.a[maxsuffp].link].len);
            pathways -= ta.a[minsuffp].linkPaths;
            pathways -= ta.a[minsuffp].pathsFrom * (minsuff-1 - ta.a[ta.a[minsuffp].link].len);
        }
        if(pref == len) {
            pathways += sa.a[prefp].pathsFrom * ta.a[0].pathsFrom;
        }
        return tuple{len, pref, prefp, maxsuff, maxsuffp, minsuff, minsuffp, curways, pathways};
    };

    string w;
    int len = 0, pref = 0, prefp = 0, maxsuff = 0, maxsuffp = 0, minsuff = 0, minsuffp = 0;
    while(k > 0) {
        bool found = false;
        rep(c, 'a', 'z'+1) {
            auto [len1, pref1, prefp1, maxsuff1, maxsuffp1, minsuff1, minsuffp1, curways, pathways] = 
                addchar(c, len, pref, prefp, maxsuff, maxsuffp, minsuff, minsuffp);
            if(pathways < k) {
                k -= pathways;
            } else {
                found = true;
                k -= curways;
                tie(len, pref, prefp, maxsuff, maxsuffp, minsuff, minsuffp) = 
                    tie(len1, pref1, prefp1, maxsuff1, maxsuffp1, minsuff1, minsuffp1);
                w += c;
                break;
            }
        }
        if(!found) {
            break;
        }
    }
    if(k > 0) return "";
    return w;
}



int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    string s, t; cin >> s >> t;

    long long k; cin >> k;
    string ans = solve(s, t, k);
    if(sz(ans) == 0) cout << "-1\n";
    else cout << ans << "\n";
    
    return 0;
}
