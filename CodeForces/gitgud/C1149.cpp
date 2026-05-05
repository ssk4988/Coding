#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pi = pair<int, int>;
using pl = pair<ll, ll>;
using pd = pair<ld, ld>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vpi = vector<pi>;
using vpl = vector<pl>;
using vpd = vector<pd>;
using vvi = vector<vi>;

#define f first
#define s second
#define mp make_pair
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define nL "\n"


/*
segment - multiplier
0 - 0
1 - 1
2 - -1
3 - 0
can just do matrix multiplication but we can optimize it
0-0 is always 0
0-1 is suffix max - 0
0-2 is cut peak - 1
0-3 is answer - 2
1-1 is sum - 3
1-2 is peak - 4
1-3 is peak cut - 5
2-2 is -sum
2-3 is -prefix min - 6
3-3 is always 0
*/
// using S = array<int, 7>;
// S id(int t=-1) {
//     return S{max(0, t), 1, 1, t, 1, 1, max(0, -t)};
// }

// S operator+(S a, S b) {
//     return S{max(a[0]+b[3],b[0]),max({b[1],a[0]+b[4],a[1]-b[3]}),max({b[2],a[0]+b[5],a[1]+b[6],a[2]}),
//     a[3]+b[3],max(a[3]+b[4],a[4]-b[3]),max({a[3]+b[5],a[4]+b[6],a[5]}),max(-a[3]+b[6],a[6])};
// }

using S = array<array<int, 4>, 4>;
array<int, 4> mult{0, 1, -1, 0};
S id(int t = -1) {
    S res;
    for(int i = 3; i >= 0; i--) {
        res[i][i] = mult[i] * t;
        rep(j, i+1, 4) {
            res[i][j] = max(res[i][j-1], res[j][j]);
        }
    }
    return res;
}
S operator+(S a, S b) {
    S res;
    rep(i, 0, 4) {
        rep(j, i, 4) {
            res[i][j] = -1e9;
            rep(k, i, j+1) {
                res[i][j] = max(res[i][j], a[i][k]+b[k][j]);
            }
        }
    }
    return res;
}

struct Node {
    int lo, hi;
    Node *l=0, *r=0;
    S val;
    Node(int lo, int hi) : lo(lo), hi(hi), val(id(-1)) {
        if(lo+1<hi) {
            int mid = lo + (hi-lo)/2;
            l=new Node(lo, mid), r=new Node(mid, hi);
            val = l->val + r->val;
        }
    }
    void set(int idx, S x) {
        if(lo+1==hi) return void(val = x);
        int mid = lo + (hi-lo)/2;
        (mid <= idx ? r : l)->set(idx, x);
        val = l->val + r->val;
    }
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);    
    int n, q; cin >> n >> q;
    Node tree(0, 2*n-2);
    string s; cin >> s;
    rep(i, 0, 2*n-2) {
        tree.set(i, id(s[i] == ')' ? 1 : -1));
    }
    cout << tree.val[0][3] << "\n";
    rep(i, 0, q) {
        int u, v; cin >> u >> v;
        u--, v--;
        swap(s[u], s[v]);
        tree.set(u, id(s[u] == ')' ? 1 : -1));
        tree.set(v, id(s[v] == ')' ? 1 : -1));
        cout << tree.val[0][3] << "\n";
    }
    return 0;
}
