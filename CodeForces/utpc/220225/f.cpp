#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()

using ll = long long;
using vi = vector<int>;
using pi = pair<int, int>;

struct Node {
    Node *l = 0, *r = 0;
    int lo, hi, mx = 0;
    Node(int lo, int hi): lo(lo), hi(hi){}
    int query(int L, int R){
        if(R <= lo || hi <= L) return 0;
        if(L <= lo && hi <= R) return mx;
        push();
        return max(l->query(L, R), r->query(L, R));
    }
    void upd(int idx, int x){
        if(idx + 1 <= lo || hi <= idx) return;
        if(lo + 1 == hi){
            mx = max(x, mx);
        }
        else{
            push();
            int mid = lo + (hi - lo) / 2;
            if(mid <= idx) r->upd(idx, x);
            else l->upd(idx, x);
            mx = max(l->mx, r->mx);
        }
    }
    void push(){
        if(!l){
            int mid = lo + (hi - lo) / 2;
            l = new Node(lo, mid); r = new Node(mid, hi);
        }
    }
};

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, k; cin >> n >> k;
    vi a(n);
    rep(i, 0, n) cin >> a[i];
    int maxval = 1e9 + 100;
    // Node pref(0, maxval), suff(0, maxval);
    vi prefdp(n), suffdp(n);
    rep(i, 0, n){
        prefdp[i] = 1 + (i > 0 && a[i] > a[i - 1] ? prefdp[i - 1] : 0);
        // pref.upd(a[i], prefdp[i]);
    }
    for(int i = n - 1; i >= 0; i--){
        suffdp[i] = 1 + (i + 1 < n && a[i] < a[i + 1] ? suffdp[i + 1] : 0);
        // suff.upd(a[i], suffdp[i]);
    }
    int ans = 0;
    rep(i, 0, n){
        ans = max(ans, prefdp[i]);
        if(i + k + 1 < n && a[i] < a[i + k + 1]){
            ans = max(ans, prefdp[i] + suffdp[i + k + 1]);
        }
    }
    cout << ans << "\n";
}