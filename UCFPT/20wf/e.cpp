#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)

using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<pii>;
using vvi = vector<vi>;

struct Node {
    int lo, hi;
    Node *l = 0, *r = 0;
    ll a=0, b=0;
    Node(int lo, int hi) : lo(lo), hi(hi) {
        if(lo + 1 < hi){
            int mid = lo + (hi - lo) / 2;
            l = new Node(lo, mid), r = new Node(mid, hi);
        }
    }
    void push() {
        if(!l) return;
        if(a == 0 && b == 0) return;
        l->add(lo, hi, a, b);
        r->add(lo, hi, a, b);
        a = 0;
        b = 0;
    }
    void add(int L, int R, ll lin, ll con) {
        if(R <= lo || hi <= L) return;
        if(L <= lo && hi <= R) {
            a += lin;
            b += con;
            // b += con + lin * (lo - L);
            // cout << "add on " << lo << "," << hi << " a=" << lin << " b=" << con << "\n";
            return;
        }
        push(), l->add(L, R, lin, con), r->add(L, R, lin, con);
    }
    void dfs() {
        push();
        if(!l) {
            cout << (a * lo + b) << "\n";
        }
        else l->dfs(), r->dfs();
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, q; cin >> n >> q;
    Node tree(0, n);
    rep(_, 0, q){
        string t; cin >> t;
        int l, r; cin >> l >> r; l--;
        int mid = l + (r - l) / 2;
        // cout << t << " " << l << " " << r << "\n";
        if(t == "R") tree.add(l, r, 0, 1);
        else if(t == "D") tree.add(l, r, 0, -1);
        else if(t == "H") {
            tree.add(l, mid, 1, -(l-1));
            tree.add(mid, r, -1, r);
        } else {
            tree.add(l, mid, -1, (l-1));
            tree.add(mid, r, 1, -r);
            // tree.add(l, mid, -1, mid);
            // tree.add(mid, r, 1, -(mid-1));
        }
    }
    tree.dfs();
    

    return 0;
}
