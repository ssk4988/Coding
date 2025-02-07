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

const bool DEBUG = false;
const bool TEST = false;


const ll lim = 8.5e18;
ll add(ll a, ll b) {
    return a + b;
    // ll blim = lim - a;
    // return b <= blim ? a+b : lim;
}
ll mult(ll a, ll b) {
    return a * b;
    // if(a == 0) return 0;
    // ll blim = lim / a;
    // return b <= blim ? a*b : lim;
}

struct st {int len, pos, term, link=-1;
    vi next, linknext;
    // map<char, int> next, linknext;
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
                a[u].linkPaths = add(a[p].linkPaths, mult(a[p].pathsFrom, linklen));
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
        if(DEBUG) {
            rep(i, 0, n) {
                cerr << "automaton node " << i << ": len " << a[i].len << " link " << a[i].link << 
                    "pathsfrom: " << a[i].pathsFrom << " linkpaths " << a[i].linkPaths << endl;
                cerr << "transitions: ";
                rep(key, 0, 26){
                    if(a[i].next[key] == -1) continue;
                    cerr << key << "," << a[i].next[key] << " ";
                }
                cerr << endl;
            }
        }
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

string solve_brute(string s, string t, ll k) {
    set<string> ssub, tsub;
    rep(i, 0, sz(s)){
        rep(j, i+1, sz(s)+1) {
            ssub.insert(s.substr(i, j-i));
        }
    }
    rep(i, 0, sz(t)) {
        rep(j, i+1, sz(t)+1) {
            tsub.insert(t.substr(i, j-i));
        }
    }
    vector<string> papers;
    for(auto &ss : ssub) {
        for(auto &ts : tsub) {
            papers.pb(ss + ts);
        }
    }
    sort(all(papers));
    if(sz(papers) < k) 
    {
        // cerr << "not possible\n";
        return "";
    }
    // cerr << "actual ans: " << papers[k-1] << "\n";
    if(DEBUG && !TEST) {
        cerr << "strings: " << endl;
        rep(i, 0, min(sz(papers) + ll(0), k+10)){
            cerr << papers[i] << endl;
        }
        cerr << endl;
    }
    return papers[k-1];
}

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
            // while(maxsuffp > 0 && !ta.a[maxsuffp].next[c] != -1) {
            //     maxsuffp = ta.a[maxsuffp].link;
            //     maxsuff = ta.a[maxsuffp].len;
            // }
            if(ta.a[maxsuffp].linknext[c] != -1) {
                int msp = ta.a[maxsuffp].linknext[c];
                if(msp != maxsuffp) maxsuff = ta.a[msp].len;
                maxsuffp = msp;
            } else maxsuffp = maxsuff = 0;
            if(ta.a[maxsuffp].next[c] != -1) {
                maxsuffp = ta.a[maxsuffp].next[c];
                maxsuff++;
            }

            // while(minsuffp > 0 && !ta.a[minsuffp].next[c] != -1) {
            //     minsuffp = ta.a[minsuffp].link;
            //     minsuff = ta.a[minsuffp].len;
            // }
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
        // assert(len == 1 || (maxsuffp > 0 && minsuffp > 0));
        if(DEBUG) cerr << "adding " << c << ", now " << pref << " " << prefp << " " << maxsuff << " " << maxsuffp
        << " " << minsuff << " " << minsuffp << endl;
        if(len == 1) {
            assert(maxsuffp == 0 && minsuffp == 0 && maxsuff == 0 && minsuff == 0);
            curways = 0;
            // pathways = ta.a[maxsuffp].pathsFrom;
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


    cerr << "use overflow ops everywhere" << endl;
    string w;
    int len = 0, pref = 0, prefp = 0, maxsuff = 0, maxsuffp = 0, minsuff = 0, minsuffp = 0;
    while(k > 0) {
        bool found = false;
        if(DEBUG) {
            cerr << "string is now " << w << endl;
            cerr << "len " << len << " pref " << pref << " prefp " << prefp << " maxsuff " << maxsuff << 
                "maxsuffp " << maxsuffp << " minsuff " << minsuff << " minsuffp " << minsuffp << endl;
        }
        rep(c, 'a', 'z'+1) {
            auto [len1, pref1, prefp1, maxsuff1, maxsuffp1, minsuff1, minsuffp1, curways, pathways] = 
                addchar(c, len, pref, prefp, maxsuff, maxsuffp, minsuff, minsuffp);
            if(DEBUG && pathways) {
                cerr << "try " << char(c) << " on prefix of " << w << ", k=" << k << endl;
                cerr << "attempt curways: " << curways << " " << pathways << endl;
            }
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

random_device rd;
mt19937 rng;
tuple<string, string, ll> generate() {
    uniform_int_distribution<int> sizegen(1, 100);
    int n = sizegen(rng), m = sizegen(rng);
    uniform_int_distribution<long long> kgen(1, 10);
    uniform_int_distribution<int> cgen(0, 25);
    ll k = kgen(rng);
    string s, t;
    rep(i, 0, n) {
        s.pb('a' + cgen(rng));
    }
    rep(i, 0, m) {
        t.pb('a' + cgen(rng));
    }
    cerr << n << " " << m << endl;
    return {s, t, k};
}


int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    rng = mt19937(rd());
    if(!TEST) {
        string s, t; cin >> s >> t;

        long long k; cin >> k;
        string ans = solve(s, t, k);
        if(sz(ans) == 0) cout << "-1\n";
        else cout << ans << "\n";
        // string ans_brute = solve_brute(s, t, k);
        // cout << ans_brute << endl;
    } else {
        while(true) {
            auto [s, t, k] = generate();
            string ans_brute = solve_brute(s, t, k);
            string ans = solve(s, t, k);
            if(ans != ans_brute) {
                cerr << "break case: \n";
                cerr << s << "\n" << t << "\n" << k << "\n";
                cerr << ans_brute << "\n" << ans << "\n";
                break;
            }
        }
    }
    
    
    return 0;
}
