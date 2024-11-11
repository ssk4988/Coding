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
using ull = unsigned long long;

#define f first
#define s second
#define mp make_pair
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define all(x) begin(x), end(x)
#define sz(x) (int)size(x)
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define nL "\n"

const int ABSIZE = 27;

int chrint(char c){
    if(c == ' ') return 26;
    return c - 'a';
}
 
struct node {
	int nxt[ABSIZE];
	vi ids = {};
	int prv = -1, link = -1;
	int c;
	int linkMemo[ABSIZE];
    ull hsh = 0;
 
	node(int prv = -1, int c = '$'): prv(prv), c(c) {
		fill(all(nxt), -1);
		fill(all(linkMemo), -1);
	}
};
 
vector<node> trie(1);
 
void addWord(string &s, int id, ull hsh) {
	int cur = 0;
	for(char c: s) {
		int idx = chrint(c);
		if(trie[cur].nxt[idx] == -1) {
			trie[cur].nxt[idx] = sz(trie);
			trie.emplace_back(cur, c);
		}
		cur = trie[cur].nxt[idx];
	}
	trie[cur].ids.push_back(id);
    trie[cur].hsh += hsh;
}
 
int getLink(int cur);
 
int calc(int cur, char c) {
	int idx = chrint(c);
	auto &ret = trie[cur].linkMemo[idx];
	if(ret != -1) return ret;
	if(trie[cur].nxt[idx] != -1)
		return ret = trie[cur].nxt[idx];
	return ret = cur == 0 ? 0 : calc(getLink(cur), c);
}
 
int getLink(int cur) {
	auto &ret = trie[cur].link;
	if(ret != -1) return ret;
	if(cur == 0 || trie[cur].prv == 0) return ret = 0;
	return ret = calc(getLink(trie[cur].prv), trie[cur].c);
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m, k; cin >> n >> m >> k;
    string line;
    getline(cin, line);
    vector<string> uni(n);
    rep(i, 0, n){
        getline(cin, uni[i]);
    }
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    vector<ull> hsh(n);
    vector<ull> edhsh(m);
    vpi ed(m);
    rep(i, 0, m){
        cin >> ed[i].f >> ed[i].s;
        ed[i].f--, ed[i].s--;
        edhsh[i] = rng();
        hsh[ed[i].f] += edhsh[i];
        hsh[ed[i].s] -= edhsh[i];
    }
    rep(i, 0, n){
        addWord(uni[i], i, hsh[i]);
    }
    rep(i, 1, sz(trie)){
        trie[i].hsh += trie[getLink(i)].hsh;
    }
    getline(cin, line);
    rep(i, 0, k){
        ull tot = 0;
        getline(cin, line);
        int cur = 0;
        for(char c : line){
            cur = calc(cur, c);
            tot += trie[cur].hsh;
        }
        cout << (tot == 0 ? "yes" : "no") << "\n";
    }

    
    return 0;
}
