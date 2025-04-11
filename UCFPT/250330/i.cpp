#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;
using vl = vector<ll>;

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)
struct node {
    int val;
    node *nxt=nullptr, *prv=nullptr;
    node(int val):val(val){}
};
struct Linked {
    vector<node*> mp;
    int s=0;
    Linked() : mp(1e6+10){}
    void rem(int v) {
        node *p = mp[v];
        node *prv = p->prv, *nxt = p->nxt;
        prv->nxt = nxt;
        nxt->prv = prv;
        mp[v] = nullptr;
        s--;
    }
    void insert(int y, int z) {
        node *v = new node(y);
        node *after = mp[z];
        node *before = after->prv;
        before->nxt = v;
        v->prv = before;
        after->prv = v;
        v->nxt = after;
        mp[y] = v;
        s++;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n; cin >> n;
    Linked li;
    int first;
    rep(i, 0, n) {
        int v; cin >> v;
        if(i == 0) {
            li.mp[v] = new node(v);
            li.mp[v]->nxt = li.mp[v]->prv = li.mp[v];
            first = v;
        } else {
            li.insert(v, first);
        }
    }
    li.s = n;
    int q; cin >> q;
    rep(qid, 0, q) {
        string s; cin >> s;
        if(s == "-") {
            int x; cin >> x;
            li.rem(x);
        }
        else if(s == "+") {
            int y, z; cin >> y >> z;
            li.insert(y, z);
        } else {
            int k; cin >> k;
            vi a(k);
            rep(i, 0, k) cin >> a[i];
            // cerr << "before query: ";
            // dfs(root);
            // cerr << endl;
            int window = 0;
            int r = 0;
            node *right;
            vi jmpsize(k), jmp(k, -1);
            rep(l, 0, k) {
                while(window + 1 <= k) {
                    if(window == 0) {
                        r = l;
                        if(li.mp[a[r]]) {
                            right = li.mp[a[r]];
                            window++;
                            r = (r+1) % k;
                        } else {
                            break;
                        }
                    }
                    else {
                        node *nxt = right->nxt;
                        // cerr << "nxt of " << right->val << " is " << nxt->val << endl;
                        if(nxt->val != a[r]) break;
                        right = nxt;
                        window++;
                        r = (r+1)%k;
                    }
                }
                jmp[l] = r;
                jmpsize[l] = window;
                // cerr << l << " " << r << " " << window << endl;
                if(window) window--;
            }
            vi state(k);
            vi ans(k);
            auto calc = [&](int u, auto &&calc) -> bool {
                if(state[u]) {
                    return state[u] == 1;
                }
                state[u] = 1;
                ans[u] = jmpsize[u];
                if(jmpsize[u] == k) {
                    bool cycle = calc(jmp[u], calc);
                    if(cycle) return true;
                    ans[u] = jmpsize[u] + ans[jmp[u]];
                } 
                state[u] = 2;
                return false;
            };
            bool cycle = false;
            rep(i, 0, k) {
                bool ret = calc(i, calc);
                if(ret) cycle = true;
            }
            if(cycle && k % li.s == 0){
                cout << "*\n";
            } else {
                cout << *max_element(all(ans)) << "\n";
            }
        }
    }

    return 0;
}
