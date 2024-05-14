#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;

#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)


struct Node {
    int nxt[26];
    int suff = 0;
    int cnt = 0;
    vi id;
};
const int MAX_N = 4e6;
Node t[MAX_N];
int curnodes = 2;

int create() {
    return curnodes++;
}

void addBackward(int n, string &s, int idx, int id, int lim){
    if(idx == lim) return t[n].id.push_back(id);
    int c = s[idx] - 'a';
    if(!t[n].nxt[c]) t[n].nxt[c] = create();
    addBackward(t[n].nxt[c], s, idx-1, id, lim);
}

void addForward(int n, string &s, int idx, int id){
    if(s[idx] == '*') {
        if(!t[n].suff) t[n].suff = create();
        addBackward(t[n].suff, s, sz(s) - 1, id, idx);
        return;
    }
    int c = s[idx] - 'a';
    if(!t[n].nxt[c]) t[n].nxt[c] = create();
    addForward(t[n].nxt[c], s, idx+1, id);
}

void updBackward(int n, string &s, int idx, int lim) {
    t[n].cnt++;
    // cout << "add 1 at " << n << " with string " << s << " idx " << idx << " lim " << lim << endl;
    if(idx == lim) return;
    int c = s[idx] - 'a';
    if(t[n].nxt[c]) updBackward(t[n].nxt[c], s, idx-1, lim);
}

void updForward(int n, string &s, int idx) {
    if(t[n].suff)updBackward(t[n].suff, s, sz(s) - 1, idx-1);
    if(idx >= sz(s)) return;
    int c = s[idx] - 'a';
    if(t[n].nxt[c]) updForward(t[n].nxt[c], s, idx+1);
}
vi ans;
void dfs(int n) {
    for(int i : t[n].id) ans[i] = t[n].cnt;
    if(t[n].suff) dfs(t[n].suff);
    rep(i, 0, 26) if(t[n].nxt[i]) dfs(t[n].nxt[i]);
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, q; cin >> n >> q;
    vector<string> words(n), queries(q);
    rep(i, 0, n){
        cin >> words[i];
    }
    rep(i, 0, q){
        cin >> queries[i];
        addForward(1, queries[i], 0, i);
    }
    rep(i, 0, n){
        updForward(1, words[i], 0);
    }
    ans.resize(q);
    dfs(1);
    rep(i, 0, q){
        cout << ans[i] << "\n";
    }
    return 0;
}
