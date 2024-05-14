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


vpi cost;
const int MAX_B = 201;

struct AhoCorasick {
	enum {alpha = 26, first = 'A'}; // change this!
	struct Node {
		// (nmatches is optional)
		int back, next[alpha], start = -1, end = -1, nmatches = 0, score = 0;
        int dp[MAX_B];
		Node(int v) { memset(next, v, sizeof(next)); memset(dp, -1, sizeof(dp)); }
	};
	vector<Node> N;
	vi backp;
	void insert(string& s, int j, int score) {
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
		N[n].nmatches++;
        N[n].score += score;
	}
	AhoCorasick(vector<string>& pat, vi &scores) : N(1, -1) {
		rep(i,0,sz(pat)) insert(pat[i], i, scores[i]);
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
                    N[ed].score += N[y].score;
					q.push(ed);
				}
			}
		}
	}
	vi find(string word) {
		int n = 0;
		vi res; // ll count = 0;
		for (char c : word) {
			n = N[n].next[c - first];
			res.push_back(N[n].end);
			// count += N[n].nmatches;
		}
		return res;
	}
	vector<vi> findAll(vector<string>& pat, string word) {
		vi r = find(word);
		vector<vi> res(sz(word));
		rep(i,0,sz(word)) {
			int ind = r[i];
			while (ind != -1) {
				res[i - sz(pat[ind]) + 1].push_back(ind);
				ind = backp[ind];
			}
		}
		return res;
	}
    int solve(int len){
        N[0].dp[0] = 0;
        rep(j, 0, MAX_B){
            rep(i, 0, sz(N)){
                if(N[i].dp[j] < 0) continue;
				for(auto [c, co] : cost){
					if(j + co > MAX_B) continue;
                // rep(k, 0, 26){
                    int i1 = N[i].next[c];
                    N[i1].dp[j + co] = max(N[i1].dp[j + co], N[i].dp[j] + N[i1].score);
                }
            }
        }
        int ans = 0;
        rep(j, 0, len + 1){
            rep(i, 0, sz(N)){
                ans = max(ans, N[i].dp[j]);
            }
        }
        return ans;
    }
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n, m, b; cin >> n >> m >> b;
        cost.clear();
        rep(i, 0, n){
            char h; int c; cin >> h >> c;
			cost.pb({h - 'A', c});
        }
        vector<string> strs(m);
        vi scores(m);
        rep(i, 0, m){ 
            cin >> strs[i] >> scores[i];
        }
        AhoCorasick ac(strs, scores);
        cout << "Case #" << (cn + 1) << ": " << ac.solve(b) << nL;
        
    }
    
    return 0;
}
