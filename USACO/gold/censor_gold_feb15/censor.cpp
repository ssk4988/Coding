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

#define mp make_pair
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define nL "\n"

struct AhoCorasick
{
	enum
	{
		alpha = 26,
		first = 'a'
	}; // change this!
	struct Node
	{
		// (nmatches is optional)
		int back, next[alpha], start = -1, end = -1, nmatches = 0;
		Node(int v) { memset(next, v, sizeof(next)); }
	};
	vector<Node> N;
	vi backp;
	void insert(string &s, int j)
	{
		assert(!s.empty());
		int n = 0;
		for (char c : s)
		{
			int &m = N[n].next[c - first];
			if (m == -1)
			{
				n = m = sz(N);
				N.emplace_back(-1);
			}
			else
				n = m;
		}
		if (N[n].end == -1)
			N[n].start = j;
		backp.push_back(N[n].end);
		N[n].end = j;
		N[n].nmatches++;
	}
	AhoCorasick(vector<string> &pat) : N(1, -1)
	{
		rep(i, 0, sz(pat)) insert(pat[i], i);
		N[0].back = sz(N);
		N.emplace_back(0);

		queue<int> q;
		for (q.push(0); !q.empty(); q.pop())
		{
			int n = q.front(), prev = N[n].back;
			rep(i, 0, alpha)
			{
				int &ed = N[n].next[i], y = N[prev].next[i];
				if (ed == -1)
					ed = y;
				else
				{
					N[ed].back = y;
					(N[ed].end == -1 ? N[ed].end : backp[N[ed].start]) = N[y].end;
					N[ed].nmatches += N[y].nmatches;
					q.push(ed);
				}
			}
		}
	}
	vi find(string word)
	{
		int n = 0;
		vi res; // ll count = 0;
		for (char c : word)
		{
			n = N[n].next[c - first];
			res.push_back(N[n].end);
			// count += N[n].nmatches;
		}
		return res;
	}
	vector<vi> findAll(vector<string> &pat, string word)
	{
		vi r = find(word);
		vector<vi> res(sz(word));
		rep(i, 0, sz(word))
		{
			int ind = r[i];
			while (ind != -1)
			{
				res[i - sz(pat[ind]) + 1].push_back(ind);
				ind = backp[ind];
			}
		}
		return res;
	}
};

int main()
{
	cin.tie(0)->sync_with_stdio(0);
    freopen("censor.in", "r", stdin);
    freopen("censor.out", "w", stdout);
	string str;
	cin >> str;
	int n;
	cin >> n;
	vector<string> pat;
	rep(i, 0, n)
	{
		string k;
		cin >> k;
		pat.pb(k);
	}
	AhoCorasick ac = AhoCorasick(pat);
	int cur = 0;
	vector<char> word;
	vector<int> loc;
	loc.pb(cur);
	rep(i, 0, str.length())
	{
		word.pb(str[i]);
		cur = ac.N[cur].next[str[i] - ac.first];
		loc.pb(cur);
		if (ac.N[cur].end != -1)
		{
			int k = pat[ac.N[cur].end].length();
			rep(j, 0, k)
			{
				loc.pop_back();
				word.pop_back();
			}
			cur = loc.back();
		}
		
	}
	rep(i, 0, word.size())
	{
		cout << word[i];
	}
	cout << nL;

	return 0;
}