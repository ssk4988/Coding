#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;
using ll = long long;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int)x.size()
#define all(x) begin(x), end(x)

const int inf = 1e9;
struct Node {
    Node *l = 0, *r = 0;
    int lo, hi, val = -inf, madd = 0;
    Node(int lo, int hi) : lo(lo), hi(hi) {
        if(lo + 1 < hi){
            int mid = lo + (hi - lo) / 2;
            l = new Node(lo, mid), r = new Node(mid, hi);
            val = min(l->val, r->val);
        }
        else val = 0;
    }
    void add(int L, int R, int x) {
        if(R <= lo || hi <= L) return ;
        if(L <= lo && hi <= R) {
            madd += x, val += x;
        }
        else{
            push(), l->add(L, R, x), r->add(L, R, x);
            val = min(l->val, r->val);
        }
    }
    void push() {
        if(madd) l->add(lo, hi, madd), r->add(lo, hi, madd), madd = 0;
    }
};

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int m, n; cin >> m >> n;
    int lo = 0, hi = n / 2;
    vi v(n);
    Node tree(0, m + 1);
    rep(i, 0, n) cin >> v[i];
    int ans = 0;
    // int rleft = 
    rep(k, 1, n + 1){
        if(2 * k > n) break;
        tree.add(0, v[k - 1] + 1, -1);
        if(k > 1){
            tree.add(0, v[k - 1], -1);
        }
        if(k == 1){
            tree.add(0, v[k], 1);
        }
        else{
            tree.add(0, v[2 * k - 2], 1);
            tree.add(0, v[2 * k - 1], 1);
        }
        if(tree.val >= 0) ans = max(ans, k);
        // if(tree.val >= 0) cout << "works on k=" << k << "\n";
    }
    cout << ans << "\n";
    return 0;
}
