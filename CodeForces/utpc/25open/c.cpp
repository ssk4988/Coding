#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vl = vector<ll>;
using pll = pair<ll, ll>;

#define sz(x) (int)x.size()
#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)

struct st {int len, pos, term, link=-1; map<char, int> next;};
struct SuffixAutomaton {
    vector<st> a;
    vi lasts;
    SuffixAutomaton(string &str) {
        a.resize(1);
        int last = 0;
        for(auto c : str) {
            int p = last, cur = last = sz(a);
            a.push_back({a[p].len+1, a[p].len});
            while(p >= 0 && !a[p].next.count(c))
                a[p].next[c] = cur, p = a[p].link;
            if(p == -1) a[cur].link = 0;
            else {
                int q = a[p].next[c];
                if(a[p].len + 1 == a[q].len) a[cur].link = q;
                else {
                    a.push_back({a[p].len+1, a[q].pos, 0, a[q].link, a[q].next});
                    for(; p >= 0 && a[p].next[c] == q; p = a[p].link)
                        a[p].next[c] = sz(a)-1;
                    a[q].link = a[cur].link = sz(a)-1;
                }
            }
            lasts.push_back(last);
        }
        while(last >= 0) a[last].term = 1, last = a[last].link;
    }
};
pll operator+(pll a, pll b) {
    return {a.first+b.first, a.second + b.second};
}
struct Node {
    int lo, hi;
    Node *l=0, *r=0;
    ll cnt=0, sum=0;
    Node(int lo, int hi) : lo(lo), hi(hi) {}
    void pull() {
        cnt = l->cnt+r->cnt;
        sum = l->sum+r->sum;
    }
    void change(int idx, ll d) {
        if(lo+1==hi) {
            cnt += d;
            sum += d * lo;
            return;
        }
        push();
        int mid = lo + (hi-lo)/2;
        (mid <= idx ? r : l)->change(idx, d);
        pull();
    }
    pll query(int L, int R) {
        if(R <= lo || hi <= L) return {0, 0};
        if(L <= lo && hi <= R){
            return {cnt, sum};
        } 
        push();
        return l->query(L, R)+r->query(L, R);
    }
    void push() {
        if(!l) {
            int mid = lo + (hi-lo)/2;
            l = new Node(lo, mid), r = new Node(mid, hi);
            pull();
        }
    }
    void clear() {
        if(l) {
            l->clear();
        }
        if(r) r->clear();
        free(this);
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, q; cin >> n >> q;
    string s; cin >> s;
    SuffixAutomaton sa(s);
    int m = sz(sa.a);
    vvi jmp(20, vi(m));
    vvi child(m);
    vector<set<int>> endpos(m);
    vector<Node> trees(m, Node(0, n+5));
    rep(i, 0, m) {
        jmp[0][i] = sa.a[i].link;
        if(sa.a[i].link != -1) {
            child[sa.a[i].link].push_back(i);
        }
        // cerr << i << " " << sa.a[i].link << endl;
    }
    rep(i, 0, sz(sa.lasts)) {
        endpos[sa.lasts[i]].insert(i);
    }
    rep(p, 1, sz(jmp)){
        rep(i, 0, m) {
            if(jmp[p-1][i] == -1) jmp[p][i] = -1;
            else jmp[p][i] = jmp[p-1][jmp[p-1][i]];
        }
    }
    vector<vector<pll>> qs(m); // {qid, length}
    rep(i, 0, q) {
        int l, r; cin >> l >> r; int len = r-l+1;
        l--, r--;
        int u = sa.lasts[r];
        for(int p = sz(jmp)-1; p >= 0; p--) {
            if(jmp[p][u] != -1 && sa.a[jmp[p][u]].len >= len) u = jmp[p][u];
        }
        qs[u].push_back({i, len});
    }
    vl qans(q, -1);
    auto dfs = [&](int u, auto &&dfs) -> void {
        int heavy = -1;
        for(int v : child[u]) {
            dfs(v, dfs);
            if(heavy == -1 || sz(endpos[heavy]) < sz(endpos[v])) {
                heavy = v;
            }
        }
        if(heavy != -1) {
            swap(endpos[u], endpos[heavy]);
            swap(trees[u], trees[heavy]);
        }
        for(int v : child[u]) {
            for(int pos : endpos[v]) {
                auto nxt = endpos[u].lower_bound(pos);
                bool hasprv = false;
                auto prv = end(endpos[u]);
                if(nxt != begin(endpos[u])) {
                    hasprv = true;
                    prv = prev(nxt);
                }
                if(hasprv && nxt != end(endpos[u])) {
                    int len = *nxt - *prv;
                    trees[u].change(len, -1);
                }
                if(hasprv) {
                    int len = pos - *prv;
                    trees[u].change(len, 1);
                }
                if(nxt != end(endpos[u])) {
                    int len = *nxt - pos;
                    trees[u].change(len, 1);
                }
                endpos[u].insert(pos);
            }
            endpos[v] = {};
            if(trees[v].l) trees[v].l->clear();
            if(trees[v].r) trees[v].r->clear();
        }
        for(auto [qid, len] : qs[u]) {
            qans[qid] = sz(endpos[u]) * len;
            auto [cnt, sum] = trees[u].query(0, len);
            qans[qid] += sum;
            qans[qid] -= len * cnt;
        }
    };
    dfs(0, dfs);
    rep(i, 0, q) {
        cout << qans[i] << "\n";
    }
    

    return 0;
}
