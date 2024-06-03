#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vii = vector<pii>;
using vll = vector<pll>;;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

struct Node {
    int lo, hi, lz=0;
    pii score;
    Node *l=0, *r=0;
    Node(int lo, int hi) : lo(lo), hi(hi){
        score = {0, hi - lo};
    }
    pii comb(pii a, pii b){
        if(a.f == b.f) return {a.f, a.s + b.s};
        return min(a, b);
    }
    void add(int L, int R, int v) {
        if(R <= lo || hi <= L) return;
        if(L <= lo && hi <= R) {
            score.f += v;
            lz += v;
            return;
        }
        push(), l->add(L, R, v), r->add(L, R, v);
        score = comb(l->score, r->score);
    }
    void push() {
        if(!l) {
            int mid = lo + (hi - lo) / 2;
            l = new Node(lo, mid), r = new Node(mid, hi);
        }
        if(lz) l->add(lo, hi, lz), r->add(lo, hi, lz), lz = 0;
    }
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int q, w; cin >> q >> w;
    Node tree(0, w);
    set<pii> has;
    rep(i, 0, q){
        int x, y; cin >> x >> y;
        int v = has.count({x, y}) ? -1 : 1;
        if(has.count({x, y})) has.erase({x, y});
        else has.insert({x, y});
        tree.add(x - y, x + y, v);

        int uncover = tree.score.f == 0 ? tree.score.s : 0;
        cout << fixed << setprecision(10) << (sqrtl(2) * (w - uncover)) << "\n";
    }
    
    return 0;
}
