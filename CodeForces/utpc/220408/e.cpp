#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i, a, b) for (int i = a; i < (b); i++)
#define pb push_back
#define f first
#define s second

using vi = vector<int>;
using ll = long long;
using pi = pair<int, int>;

struct Node{
    int lo, hi;
    Node *l = 0, *r = 0;
    ll val = 0, lzadd = 0;
    Node(int lo, int hi) : lo(lo), hi(hi){
        if(lo + 1 < hi){
            int mid = lo + (hi - lo) / 2;
            l = new Node(lo, mid), r = new Node(mid, hi);
        }
    }
    void add(int L, int R, ll x){
        if(hi <= L || R <= lo) return;
        if(L <= lo && hi <= R){
            lzadd += x;
            val += x * (hi - lo);
        }
        else{
            push();
            l->add(L, R, x), r->add(L, R, x);
            val = l->val + r->val;
        }
    }
    ll query(int L, int R){
        if(hi <= L || R <= lo) return 0;
        if(L <= lo && hi <= R){
            return val;
        }
        else{
            push();
            return l->query(L, R) + r->query(L, R);
        }
    }
    void push(){
        if(lzadd){
            l->add(lo, hi, lzadd), r->add(lo, hi, lzadd);
            lzadd = 0;
        }
    }
};

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m; cin >> n >> m;
    Node tree(0, int(1e5 + 10));
    rep(i, 0, n){
        int a, b; cin >> a >> b;
        tree.add(a, b + 1, 1);
    }
    // rep(i, 0, 10){
    //     cout << i << " " << tree.query(i, i + 1) << "\n";
    // }
    rep(i, 0, m){
        int a, b; cin >> a >> b;
        cout << tree.query(a, b + 1) << "\n";
    }
}
