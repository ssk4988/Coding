#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using vvi = vector<vi>;
using vl = vector<ll>;
using vii = vector<pii>;

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)

struct Node {
    int lo, hi;
    Node *l = 0, *r = 0;
    int val = 0;
    Node(int lo, int hi) : lo(lo), hi(hi) {
        
    }
    int query(int L, int R) {
        if(R <= lo || hi <= L) return 0;
        if(L <= lo && hi <= R) return val;
        push();
        return max(l->query(L, R), r->query(L, R));
    }
    void update(int idx, int v) {
        if(lo + 1 == hi) {
            val = max(val, v);
            return;
        }
        int mid = lo + (hi - lo) / 2;
        push();
        if(mid <= idx) r->update(idx, v);
        else l->update(idx, v);
        val = max(l->val, r->val);
    }
    void push() {
        if(l) return;
        int mid = lo + (hi - lo) / 2;
        l = new Node(lo, mid), r = new Node(mid, hi);
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    int inf = 1e9+10;
    int k; cin >> k;
    Node tree(0, inf);
    rep(i, 0, n) {
        int a; cin >> a;
        int p = max(tree.query(0, a-k+1), tree.query(a+k, inf));
        tree.update(a, p+1);
    }
    cout << tree.val << "\n";

    return 0;
}