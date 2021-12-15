// This solution used to generate data

#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
int oo = -1^1<<31;

struct DSU {
    vector<int> p;
    int comps;
    DSU(int n): comps(n) {
        p.resize(n);
        for(int i = 0; i < n; ++i) p[i] = i;
    }
    int find(int x) {
        return p[x] == x ? x : (p[x] = find(p[x]));
    }
    bool join(int u, int v) {
        int p1 = find(u), p2 = find(v);
        if(p1 != p2) {
            p[p2] = p1;
            comps--;
            return true;
        }
        return false;
    }
};

namespace LCT {
    struct node;
    int get_size(node*);
    int get_subtree_value(node*);

    int get_neutral_delta() { return 0; }
    int get_neutral_value() { return 0; }
    int modify_operation(int l, int r) { return max(l, r); }
    int query_operation(int l, int r) { return max(l, r); }
    int delta_effect_on_segment(int delta, int sl) {
        if(delta == get_neutral_delta()) return delta;
        return max(delta,  sl);
    }
    int join_value_with_delta(int val, int delta) {
        if(delta == get_neutral_delta()) return val;
        return modify_operation(val, delta);
    }
    int join_deltas(int d1, int d2) {
        if(d1 == get_neutral_delta()) return d2;
        if(d2 == get_neutral_delta()) return d1;
        return modify_operation(d1, d2);
    }
    struct node {
        int node_value, subtree_value, delta, size;
        bool revert;
        node *left, *right, *parent;
        node(int value): node_value(value), subtree_value(value) {
            revert = false;
            left = right = parent = nullptr;
            delta = get_neutral_delta();
            size = 1;
        }
        bool is_root() { return parent == nullptr || (parent->left != this && parent->right != this); }
        void push() {
            if(revert) {
                revert = false, swap(left, right);
                if(left != nullptr) left->revert ^= 1;
                if(right != nullptr) right->revert ^= 1;
            }
            node_value = join_value_with_delta(node_value, delta);
            subtree_value = join_value_with_delta(subtree_value, delta_effect_on_segment(delta, size));
            if(left != nullptr) left->delta = join_deltas(left->delta, delta);
            if(right != nullptr) right->delta = join_deltas(right->delta, delta);
            delta = get_neutral_delta();
        }
        void update() {
            subtree_value = query_operation(query_operation(get_subtree_value(left), join_value_with_delta(node_value, delta)), get_subtree_value(right));
            size = 1 + get_size(left) + get_size(right);
        }
    };
    int get_subtree_value(node* root) { return root == nullptr ? get_neutral_value() : join_value_with_delta(root->subtree_value, delta_effect_on_segment(root->delta, root->size)); }
    void connect(node* ch, node* p, int is_left_child) {
        if(ch != nullptr) ch->parent = p;
        if(is_left_child != -1) {
            if(is_left_child) p->left = ch;
            else p->right = ch;
        }
    }
    void rotate(node* x) {
        node* p = x->parent, *g = p->parent;
        bool is_root_p = p->is_root(), left_child_x = (x == p->left);
        connect(left_child_x ? x->right : x->left, p, left_child_x);
        connect(p, x, !left_child_x);
        connect(x, g, is_root_p ? -1 : p == g->left);
        p->update();
    }
    void splay(node* x) {
        while(!x->is_root()) {
            node* p = x->parent, *g = p->parent;
            if(!p->is_root()) g->push();
            p->push(), x->push();
            if(!p->is_root()) rotate((x == p->left) == (p == g->left) ? p : x);
            rotate(x);
        }
        x->push(), x->update();
    }
    node* expose(node* x) {
        node* last = nullptr;
        for(node* y = x; y != nullptr; y = y->parent) {
            splay(y), y->left = last, last = y;
        }
        splay(x); return last;
    }
    void make_root(node* x) { expose(x), x->revert ^= 1; }
    bool connected(node* x, node* y) {
        if(x == y) return true;
        expose(x), expose(y);
        return x->parent != nullptr;
    }
    void link(node* x, node* y) {
        if(connected(x, y)) throw; //x and y are connected already
        make_root(x), x->parent = y;
    }
    void cut(node* x, node* y) {
        make_root(x), expose(y);
        if(y->right != x || x->left != nullptr) throw; //no edge (x, y)
        y->right = y->right->parent = nullptr;
    }
    int query(node* from, node* to) {
        make_root(from), expose(to);
        return get_subtree_value(to);
    }
    void modify(node* from, node* to, int delta) {
        make_root(from), expose(to);
        to->delta = join_deltas(to->delta, delta);
    }
    int get_size(node *root) { return root == nullptr ? 0 : root->size; }
};
using namespace LCT;

int main(){
    cin.tie(0)->sync_with_stdio(0);
    int NUM_TESTS;
    cin >> NUM_TESTS;
    while(NUM_TESTS--){
        cout.flush();
        int n, m;
        cin >> n >> m;
        vector<pair<int, pair<int, int>>> edges(m);
        vector<pair<int, pair<int, int>>> edges2(m);
        for(int i = 0; i < m; i++){
            int u, v, w;
            cin >> u >> v >> w;
            u--;v--;
            edges[i] = make_pair(w, make_pair(u, v));
            edges2[i] = make_pair(w, make_pair(u, v));
        }
        sort(edges.begin(), edges.end());
        vector<node*> oddnodes(0);
        vector<node*> evennodes(0);
        vector<int> nodeidx(n, -1);

        DSU dsu(n);
        ll mstsum = 0;
        for(auto [w, uv] : edges){
            auto [u, v] = uv;
            if(dsu.join(u,v)){                
                mstsum += w;

                if(nodeidx[u] == -1){
                    nodeidx[u] = evennodes.size();
                    evennodes.push_back(new node(0));
                    oddnodes.push_back(new node(0));
                }
                if(nodeidx[v] == -1){
                    nodeidx[v] = oddnodes.size();
                    oddnodes.push_back(new node(0));
                    evennodes.push_back(new node(0));
                }

                node *oddguy = new node(w % 2 ? w : 0);
                oddnodes.push_back(oddguy);
                link(oddnodes[nodeidx[u]], oddguy);
                link(oddnodes[nodeidx[v]], oddguy);
                
                node *evenguy = new node(w % 2 ? 0 : w);
                evennodes.push_back(evenguy);
                link(evennodes[nodeidx[u]], evenguy);
                link(evennodes[nodeidx[v]], evenguy);

                
            }
            if(dsu.comps == 1)break;
        }

        if(dsu.comps != 1){
            cout << "-1\n";
            continue;
        }

        if(mstsum % 2){
            cout << mstsum << "\n";
            continue;
        }

        // cout << n << " " << m << endl;
        // for(auto [w, p] : edges2){
        //     auto [u, v] = p;
        //     cout << u+1 << " " << v+1 << " " << w << "\n";
        // }

        // continue;



        ll bestans = -1;
        
        for(auto [w, uv] : edges){
            auto [u, v] = uv;
            ll qq = 0;
            if(w % 2 == 0){
                // this is an even edge, let's try to replace an odd edge
                qq = query(oddnodes[nodeidx[u]], oddnodes[nodeidx[v]]);
                
            }else{
                // this is an odd edge, let's try to replace an even edge
                qq = query(evennodes[nodeidx[u]], evennodes[nodeidx[v]]);
                
            }
            if(qq == 0)continue;
            if(bestans == -1) bestans = mstsum-qq+w;
            // ok so we found an odd edge on the mst from u to v
            bestans = min(bestans, mstsum-qq+w);
        }

        if(bestans % 2) cout << bestans << "\n";
        else cout << "-1\n";

    }

    return 0;
}