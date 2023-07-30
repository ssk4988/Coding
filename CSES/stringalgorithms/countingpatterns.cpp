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

struct AhoCorasick {
	enum {alpha = 26, first = 'a'}; // change this!
	struct Node {
		// (nmatches is optional)
		int back, next[alpha], start = -1, end = -1, nmatches = 0;
        vi ends;
        int trav = 0;
		Node(int v) { memset(next, v, sizeof(next)); }
	};
	vector<Node> N;
	vi backp;
	void insert(string& s, int j) {
		assert(!s.empty());
		int n = 0;
		for (char c : s) {
			int& m = N[n].next[c - first];
			if (m == -1) { n = m = sz(N); N.emplace_back(-1); }
			else n = m;
		}
		if (N[n].end == -1) N[n].start = j;
		backp.push_back(N[n].end);
		N[n].end = j;
        N[n].ends.pb(j);
		N[n].nmatches++;
	}
	AhoCorasick(vector<string>& pat) : N(1, -1) {
		rep(i,0,sz(pat)) insert(pat[i], i);
		N[0].back = sz(N);
		N.emplace_back(0);

		queue<int> q;
		for (q.push(0); !q.empty(); q.pop()) {
			int n = q.front(), prev = N[n].back;
			rep(i,0,alpha) {
				int &ed = N[n].next[i], y = N[prev].next[i];
				if (ed == -1) ed = y;
				else {
					N[ed].back = y;
					(N[ed].end == -1 ? N[ed].end : backp[N[ed].start])
						= N[y].end;
					N[ed].nmatches += N[y].nmatches;
					q.push(ed);
				}
			}
		}
	}
	vi find(string word, int v) {
		int n = 0;
		vi res(v);
        vvi child(sz(N));

        N[n].trav++
		;
		for (char c : word) {
			n = N[n].next[c - first];
            N[n].trav++;
			// res.push_back(N[n].end);
			// count += N[n].nmatches;
		}
        for(int i = sz(N) - 2; i >= 0; i--){
            child[N[i].back].pb(i);
        }
        vi dp(sz(N), -1);
        auto solve = [&](int c, auto &&solve)->int{
            if(dp[c] != -1) return dp[c];
            dp[c] = N[c].trav;
            for(int i : child[c]) dp[c] += solve(i, solve);
            return dp[c];
        };
        rep(i, 0, sz(N)){
            for(int j : N[i].ends){
                res[j] += solve(i, solve);
            }
        }
		return res;
	}
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    string str; cin >> str;
    int q; cin >> q;
    vector<string> pat(q);
    rep(i, 0, q){
        cin >> pat[i];
    }
    AhoCorasick ac(pat);
    vi res = ac.find(str, q);
    rep(i, 0, q){
        cout << res[i] << nL;
    }
    
    return 0;
}
