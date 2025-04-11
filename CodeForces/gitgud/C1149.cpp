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

struct S {
    int pmn = 0, maxpref=0, maxsuff = 0, best = 0, lm=0, mr=0, minpref=0;
};
S id(int t=-1) {
    if(t==-1) {
        return {-1, 0, 1, 1, 1, 1, -1};
    } else {
        return {1, 1, 0, 1, 1, 1, 0};
    }
}

S operator+(S a, S b) {
    int pmn = a.pmn + b.pmn;
    int best = max(a.best, b.best);
    best = max({best, a.lm + b.maxpref, a.maxsuff + b.mr});
    int maxpref = max(a.maxpref, a.pmn + b.maxpref);
    int maxsuff = max(b.maxsuff, -b.pmn + a.maxsuff);
    int minpref = min(a.minpref, a.pmn + b.minpref);
    int lm = max({a.lm + b.pmn, b.lm, a.maxsuff + (b.pmn - b.minpref) - b.minpref});
    int mr = max({a.mr, b.mr - a.pmn, b.maxpref + (a.pmn - a.minpref) - a.minpref});
    return {pmn, maxpref, maxsuff, best, lm, mr, minpref};
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
        tree.set(i, id(s[i] == '(' ? 1 : -1));
    }
    cout << tree.val.best << "\n";
    rep(i, 0, q) {
        int u, v; cin >> u >> v;
        u--, v--;
        swap(s[u], s[v]);
        tree.set(u, id(s[u] == '(' ? 1 : -1));
        tree.set(v, id(s[v] == '(' ? 1 : -1));
        cout << tree.val.best << "\n";
    }
    return 0;
}
