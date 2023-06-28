#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define pb push_back
#define f first 
#define s second
using ll = long long;
using pi = pair<int, int>;
using vi = vector<int>;
using vl = vector<ll>;
using vpi = vector<pi>;

const bool debug = false;

const ll MOD = 998244353;
ll mod(ll k){
    return k % MOD;
}
ll modpow(ll b, ll p){
    if(p == 0) return 1;
    if(p == 1) return mod(b);
    ll res = modpow(b, p/2);
    res = mod(res * res);
    if(p % 2 == 1) res = mod(res * b);
    return res;
}

struct Node {
    Node *l = 0, *r = 0;
    int lo, hi, notone = 0;
    ll sum = 0;
    int mult = 0;
    Node(vl &v, int lo, int hi) : lo(lo), hi(hi), notone(0), sum(0) {
        if(lo + 1 < hi){
            int mid = lo + (hi - lo) / 2;
            l = new Node(v, lo, mid), r = new Node(v, mid, hi);
            notone = l->notone + r->notone;
            sum = mod(l->sum + r->sum);
        }
        else{
            notone = __builtin_popcount(v[lo]) != 1;
            sum = v[lo];
        }
    }
    void add(int L, int R, int times){
        if(R <= lo || hi <= L) return;
        if(L <= lo && hi <= R && (notone == 0 || lo + 1 == hi)){
            if(notone == 0){
                mult += times;
                sum = mod(sum * modpow(2, times));
            }
            else if(notone == 1 && lo + 1 == hi){
                int sofar = 0;
                while(__builtin_popcount(sum) != 1 && sofar < times){
                    sum += sum & -sum;
                    sofar++;
                }
                if(__builtin_popcount(sum) == 1){
                    notone = 0;
                    sum = mod(sum);
                    sum = mod(sum * modpow(2, times - sofar));
                }
            }
        }
        else{
            push();
            l->add(L, R, times); r->add(L, R, times);
            notone = l->notone + r->notone;
            sum = mod(l->sum + r->sum);
        }
        if(debug) cout << "added through " << lo << "," << hi << " now val " << notone << " " << sum << "\n";
    }
    ll query(int L, int R){
        if(R <= lo || hi <= L) return 0;
        if(L <= lo && hi <= R) return sum;
        push();
        return mod(l->query(L, R) + r->query(L, R));
    }
    void push(){
        if(mult == 0) return;
        if(lo + 1 < hi){
            assert(l->notone == 0 && r->notone == 0);
            l->add(lo, hi, mult);
            r->add(lo, hi, mult);
        }
        mult = 0;
    }
};

int main() {
    if(!debug){
        cin.tie(0)->sync_with_stdio(0);
        cin.exceptions(cin.failbit);
    }
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n; cin >> n;
        vl a(n);
        rep(i, 0, n) cin >> a[i];
        Node tree(a, 0, n);
        int q; cin >> q;
        rep(i, 0, q){
            int t, l, r; cin >> t >> l >> r;
            l--,r--;
            if(t == 1){
                tree.add(l, r + 1, 1);
            }
            else{
                cout << tree.query(l, r + 1) << "\n";
            }
            t = -1;
        }
    }
}
