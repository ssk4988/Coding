#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define pb push_back
using ll = long long;
using pi = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;
using vl = vector<ll>;

struct Node {
    Node *l = 0, *r = 0;
    ll lo, hi, mid, sum = 0;
    Node (ll lo, ll hi) : lo(lo), hi(hi){
        mid = lo + (hi - lo) / 2;
    }
    void add(ll idx, ll val){
        if(idx == lo && lo + 1 == hi){
            sum += val;
        }
        else{
            push();
            if(mid <= idx) r->add(idx, val);
            else l->add(idx, val);
            sum = l->sum + r->sum;
        }
    }
    // not inclusive
    ll leftsum(ll idx){
        if(idx <= lo || hi <= 0) return 0;
        if(hi <= idx){
            return sum;
        }
        push();
        return l->leftsum(idx) + r->leftsum(idx);
    }
    void push(){
        if(!l){
            l = new Node(lo, mid); r = new Node(mid, hi);
        }
    }
};

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int q; cin >> q;
    ll maxv = 1'000'000'000'000'000LL;
    Node tree(0, maxv);
    unordered_map<ll, ll> v;
    rep(i, 0, q){
        int t; cin >> t;
        if(t == 1){
            ll val; cin >> val;
            v[i] = val;
            tree.add(val, 1);
        }
        else if(t == 2){
            int op; cin >> op; op--;
            tree.add(v[op], -1);
            v.erase(op);
        }
        else if(t == 3){
            int op; ll dif; cin >> op >> dif;
            op--;
            tree.add(v[op], -1);
            v[op] += dif;
            tree.add(v[op], 1);
        }
        else{
            int op; cin >> op; op--;
            cout << tree.leftsum(v[op]) << "\n";
        }
    }
    return 0;
}
