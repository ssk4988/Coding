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

struct Node{
    Node *par = NULL;
    Node *aut = NULL;
    ll dist = LLONG_MAX;
    int depth = 0;
    bool visited = false;
    unordered_map<Node *, ll> e;
    vector<Node *> nex;
    Node(Node *p = NULL, int d = 0): nex(26, NULL), par(p), depth(d) {}
};

void add(Node *root, string &w, bool aut=true){
    rep(i, 0, sz(w)){
        int c = w[i] - 'a';
        if(root->nex[c] == NULL) root->nex[c] = new Node(root, root->depth + 1);
        root = root->nex[c];
    }
    Node *e = root;
    if(aut && root->aut == NULL) root->aut = e;
    rep(i, 0, sz(w)){
        root = root->par;
        if(root->depth != 0 && aut && root->aut == NULL) root->aut = e;
    }
}

Node *trav(Node *root, string &w){
    rep(i, 0, sz(w)){
        int c = w[i] - 'a';
        root = root->nex[c];
    }
    return root;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, q; cin >> n >> q;
    Node *root = new Node();
    // root->par = root;
    auto dfs = [](Node *cur, auto &&dfs)->void{
        if(cur->par) cur->e[cur->par] = 1;
        if(cur->aut) cur->e[cur->aut] = 1;
        rep(i, 0, 26){
            if(cur->nex[i] != NULL) cur->e[cur->nex[i]] = 1;
        }
        rep(i, 0, 26) if(cur->nex[i] != NULL) dfs(cur->nex[i], dfs);
    };
    rep(i, 0, n){
        string str; cin >> str;
        add(root, str);
    }
    vector<string> qs(q);
    rep(i, 0, q){
        cin >> qs[i];
        add(root, qs[i], false);
    }
    // auto cmp = [](Node *a, Node *b)->bool{
    //     return a->depth > b->depth;
    // };
    dfs(root, dfs);
    using pn = pair<ll, Node*>;
    priority_queue<pn, vector<pn>, greater<pn>> pq;
    root->dist = 0;
    pq.push({0, root});
    while(!pq.empty()){
        auto [d, t] = pq.top(); pq.pop();
        if(t->visited) continue;
        t->visited = true;
        for(auto [nex, c] : t->e){
            if(t->dist + c < nex->dist){
                nex->dist = t->dist + c;
                pq.push({nex->dist, nex});
            }
        }
    }
    rep(i, 0, q){
        Node *v = trav(root, qs[i]);
        cout << v->dist << nL;
    }
    auto dfs1 = [](Node *cur, string &w, auto &&dfs1)->void{
        cout << w << " " << cur->dist << nL;
        rep(i, 0, 26){
            if(cur->nex[i] != NULL){
                w.pb(char(i + 'a'));
                dfs1(cur->nex[i], w, dfs1);
                w.pop_back();
            }
        }
    };
    string v = "";
    // dfs1(root, v, dfs1);

    
    return 0;
}
