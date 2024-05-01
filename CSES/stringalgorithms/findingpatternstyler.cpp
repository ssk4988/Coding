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
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define nL "\n"


const int ABSIZE = 26;
 
struct node {
    int nxt[ABSIZE];
    vi ids = {};
    int prv = -1, link = -1;
    char c;
	bool trav = false;
    int linkMemo[ABSIZE];
 
    node(int prv = -1, char c = '$'): prv(prv), c(c) {
        fill(all(nxt), -1);
        fill(all(linkMemo), -1);
    }
};
 
vector<node> trie(1);
 
void addWord(string &s, int id) {
    int cur = 0;
    for(char c: s) {
        int idx = c - 'a';
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
    int idx = c - 'a';
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
    string str; cin >> str;
    int q; cin >> q;
    vector<string> pat(q);
    rep(i, 0, q){
        cin >> pat[i];
		addWord(pat[i], i);
    }
	vi found(q);
	int cur = 0;
	queue<int> q2;
	q2.push(cur);
	for(char c: str){
		cur = calc(cur, c);
		q2.push(cur);
	}
	while(!q2.empty()){
		int k = q2.front();
		q2.pop();
		if(k > 0 && !trie[k].trav){
			for(int j: trie[k].ids){
				found[j] = true;
			}
			trie[k].trav = true;
			q2.push(getLink(k));
		}
	}
	rep(i, 0, q){
		if(found[i]) cout << "YES\n";
		else cout << "NO\n";
	}
	
	return 0;
}
