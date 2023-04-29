#include <bits/stdc++.h>
using namespace std;

using vi =vector<int>;
using vvi = vector<vi>;
using pi = pair<int, int>;
using ll = long long;
using vpi = vector<pair<int, int>>;
using vl = vector<ll>;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define f first
#define s second
#define pb push_back
#define nL "\n"

// struct Node{
//     Node *l = 0, *r = 0;
//     int lo, hi, val = 0;
//     Node(vi &v, int lo, int hi) : lo(lo), hi(hi) {
//         if(lo + 1 < hi){
//             int mid = lo + (hi - lo)/2;
//             l = new Node(v, lo, mid); r = new Node(v, mid, hi);
//             // val = l->val + 
//         }
//     }
//     Node(Node *other){
//         lo = other->lo;
//         hi = other->hi;
//         val = other->val;
//     }

// }

struct FT{
    vector<ll> s;
    FT(int n) : s(n){}
    void update(int pos, ll dif){
        for(; pos < sz(s); pos |= pos + 1) s[pos] += dif;
    }
    ll query(int pos){
        ll res = 0;
        for(; pos > 0; pos &= pos - 1) res += s[pos - 1];
        return res;
    }
};

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vl a(n);
    FT ft(n + 100);
    vvi occ(n + 10);
    vl fron(n);
    ll invcount = 0;
    rep(i, 0, n){
        cin >> a[i];
        fron[i] = ft.query(n + 5) - ft.query(a[i] + 1);
        invcount += fron[i];
        occ[a[i]].pb(i);
        ft.update(a[i], 1);
    }
    vl ans(n);
    for(int i = n - 1; i >= 0; i--){
        for(int k : occ[i]){
            invcount -= fron[k];
        }
        ans[i] = invcount;
    }
    rep(i, 0, n){
        cout << ans[i] << nL;
    }


    return 0;
}