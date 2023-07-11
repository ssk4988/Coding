#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;

const int SIZE = 6;

vi operator+(vi a, vi b) {
    vi c(1 << SIZE);
    rep(i, 0, 1 << SIZE)
        c[i] = a[i] + b[i];
    return c;
}

struct node {
    int lo, md, hi;
    int lazy = 0; vi val;
    node *left, *right;
    node(int s, int e, vi &m): lo(s), hi(e), md((s+e) >> 1), val(1 << SIZE) {
        if(lo == hi) {
            val[m[lo]]++;
            return;
        }
        left = new node(s, md, m);
        right = new node(md+1, e, m);
        val = left -> val + right -> val;
    }
    void shift(int v){
        if(v == 0) return;
        vi newVal(1 << SIZE);
        rep(i, 0, 1 << SIZE)
            newVal[i ^ v] = val[i];
        val = newVal;
    }
    void prop() {
        if(!lazy) return;
        if(lo != hi) {
            left -> shift(lazy);
            left -> lazy ^= lazy;
            right -> shift(lazy);
            right -> lazy ^= lazy;
        }
        lazy = 0;
    }
    void update(int s, int i) {
        if(s > hi) return;
        if(s <= lo) {
            lazy ^= (1 << i);
            shift(1 << i);
            return;
        }
        prop();
        left -> update(s, i), right -> update(s, i);
        val = left -> val + right -> val;
    }
    vi query(int s, int e) {
        if(s <= lo && hi <= e) return val;
        if(s > hi || lo > e) return vi(1 << SIZE, 0);
        prop();
        return left -> query(s, e) + right -> query(s, e);
    }
};

int main() {
    cin.tie(0) -> sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    string s; cin >> s;
    vi initMasks(sz(s) + 1);
    int curMask = 0;
    rep(i, 0, sz(s)) {
        curMask ^= (1 << (s[i] - 'a'));
        initMasks[i+1] = curMask;
    }
    node segTree(0, sz(s), initMasks);
    
    int q; cin >> q;
    while(q--) {
        int t; cin >> t;
        if(t == 1) {
            int s, e; cin >> s >> e;
            vi freq = segTree.query(s-1, e);
            ll ans = 0;
            for(int i: freq) {
                ans += (i * (ll)(i-1)) / 2;
            }
            cout << ans << '\n';
        }
        else {
            int i; char x;
            cin >> i >> x;
            segTree.update(i, s[i-1] - 'a');
            segTree.update(i, x - 'a');
            s[i] = x;
        }
    }

    return 0;
}