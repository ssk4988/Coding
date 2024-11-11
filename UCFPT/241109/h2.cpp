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
    int suffword = -1;
 
	node(int prv = -1, int c = '$'): prv(prv), c(c) {
		fill(all(nxt), -1);
		fill(all(linkMemo), -1);
	}
};
 
vector<node> trie(1);
 
void addWord(string &s, int id) {
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

struct UF {
	vi e;
	UF(int n) : e(n, -1) {}
	bool sameSet(int a, int b) { return find(a) == find(b); }
	int size(int x) { return -e[find(x)]; }
	int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
	bool join(int a, int b) {
		a = find(a), b = find(b);
		if (a == b) return false;
		if (e[a] > e[b]) swap(a, b);
		e[a] += e[b]; e[b] = a;
		return true;
	}
};

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
    vpi ed(m);
    UF uf(n);
    rep(i, 0, m){
        cin >> ed[i].f >> ed[i].s;
        ed[i].f--, ed[i].s--;
        uf.join(ed[i].f, ed[i].s);
        // cerr << ed[i].f << " " << ed[i].s << endl;
    }
    rep(i, 0, n) addWord(uni[i], i);
    vi wlink(n, -1);
    rep(i, 1, sz(trie)){
        trie[i].suffword = trie[getLink(i)].suffword;
        for(int id : trie[i].ids) {
            wlink[id] = trie[i].suffword;
            trie[i].suffword = id;
        }
    }
    // rep(i, 0, n) cerr << i << " " << wlink[i] << endl;
    vi freq(n), mx(n, INT_MIN), mn(n, INT_MAX), vis(n), comp(n);
    rep(i, 0, n) comp[uf.find(i)]++;
    getline(cin, line);
    rep(i, 0, k){
        getline(cin, line);
        vi reset;
        int cur = 0;
        for(char c : line){
            cur = calc(cur, c);
            for(int v = trie[cur].suffword; v != -1; v = wlink[v]){
                reset.pb(v);
                freq[v]++;
                if(!vis[v]) {
                    vis[v] = true;
                    comp[uf.find(v)]--;
                }
            }
        }
        bool works = true;
        // rep(i, 0, n) cerr << freq[i] << " ";
        // cerr << endl;
        for(int v : reset) mx[uf.find(v)] = max(mx[uf.find(v)], freq[v]), mn[uf.find(v)] = min(mn[uf.find(v)], freq[v]);
        for(int v : reset) if(mn[uf.find(v)] != mx[uf.find(v)] || comp[uf.find(v)]) works = false;
        for(int v : reset) {
            freq[v] = 0, mn[uf.find(v)] = INT_MAX, mx[uf.find(v)] = INT_MIN;
            if(vis[v]) comp[uf.find(v)]++, vis[v] = false;
        }
        cout << (works ? "yes" : "no") << "\n";
    }

    
    return 0;
}
