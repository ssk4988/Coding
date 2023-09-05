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
    int n, q, r; cin >> n >> q >> r;
    Node tree(0, n);
    // quality type(1 add 0 query) idx (-1 for add)
    vector<array<int, 3>> events;
    rep(i, 0, n){
        int k; cin >> k;
        events.pb({k, 1, i});
    }
    vi ans(q);
    vi l(q);
    rep(i, 0, q){
        int k; cin >> l[i] >> k; l[i]--;
        events.pb({k, 0, i});
    }
    sort(all(events));
    reverse(all(events));
    for(auto [k, t, idx] : events){
        if(t == 1){
            tree.add(idx, idx + 1, 1);
        }
        else ans[idx] = tree.query(l[idx], min(n, l[idx] + r));
    }
    rep(i, 0, q){
        cout << ans[i] << "\n";
    }
}
