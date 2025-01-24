#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vl = vector<ll>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()

struct st { int len, pos, term; st *link; map<char, st*> next; 
    ll endpos=0; 
    ll pathsTo = 0;
    ll pathsFrom = 0;
};
st *suffixAutomaton(string &str) {
    st *last = new st(), *root = last;
    for(auto c : str) {
        st *p = last, *cur = last = new st{last->len + 1, last->len};
        while(p && !p -> next.count(c))
            p->next[c] = cur, p = p->link;
        if(!p) cur->link = root;
        else {
            st *q = p->next[c];
            if(p->len + 1 == q->len) cur->link = q;
            else {
                st* clone = new st{p->len+1, q->pos, 0, q->link, q->next};
                for(; p && p->next[c] == q; p = p->link)
                    p->next[c] = clone;
                q->link = cur->link = clone;
            }
        }
        last->endpos++;
    }
    while(last) last->term = 1, last = last->link;
    return root;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    string s; cin >> s;
    st *root = suffixAutomaton(s);
    set<st*> seen;
    map<st*, vector<st*>> adj;
    map<st*, int> get_idx;
    auto dfs = [&](st *u, auto &&dfs) -> void {
        if(seen.count(u)) return;
        seen.insert(u);
        get_idx[u] = sz(get_idx);
        u->pathsFrom++;
        if(u != root) {
            adj[u->link].push_back(u);
        }
        for(auto [key, val] : u->next) {
            dfs(val, dfs);
            // cerr << "edge " << key << " from " << get_idx[u] << " to " << get_idx[val] << endl;
            u->pathsFrom += val->pathsFrom;
        }
        // cerr << "link from " << get_idx[u] << " to " << get_idx[u->link] << endl;
    };
    dfs(root, dfs);
    // cerr << "root: " << get_idx[root] << endl;
    seen.clear();
    auto findpos = [&](st *u, auto &&findpos) -> void {
        if(seen.count(u)) return;
        seen.insert(u);
        for(auto v : adj[u]) {
            findpos(v, findpos);
            u->endpos += v->endpos;
        }
    };
    findpos(root, findpos);
    seen.clear();
    vector<st*> ts;
    auto top = [&](st *u, auto &&top) -> void {
        if(seen.count(u)) return;
        seen.insert(u);
        for(auto [key, val] : u->next) {
            top(val, top);
        }
        ts.push_back(u);
    };
    top(root, top);
    reverse(all(ts));
    map<char, ll> ans;
    root->pathsTo = 1;
    for(auto u : ts) {
        for(auto [key, val] : u->next) {
            val->pathsTo += u->pathsTo;
        }
    }
    for(auto u : ts) {
        if(u != root && u->endpos != 0) {
            ll freq = u->endpos;
            for(char c : to_string(freq)) {
                // cerr << freq << " char " << c << ": " << u->pathsTo << endl;
                ans[c] += u->pathsTo;
            }
        }
        for(auto [key, val] : u->next) {
            ans[key] += u->pathsTo * val->pathsFrom;
        }
    }
    // for(auto u : ts){
    //     cerr << get_idx[u] << " " << u->endpos << " " << u->pathsFrom << " " << u->pathsTo << endl;
    // }
    for(auto [key, val] : ans){
        cout << key << " " << val << "\n";
    }
    return 0;
}