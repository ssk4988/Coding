#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int)x.size()

using ll = long long;
using vi = vector<int>;
using vl = vector<ll>;
using pii = pair<int, int>;
using pli = pair<ll, int>;
using vii = vector<pii>;
using vvi = vector<vi>;

/*
get list of suffix mins only
subtract n-1 from t to find slack
binary search on answer
now how to simulate it?
find for each stop the min time to get there
pop min time for unvisited node, visit and update transitions?
global min query for active indexes and get index
deactivate index
range chmin

range chmin only is n log n because potential function is number of distinct values in each segment
this increases by at most log n when a value is changed but when you descend you decrease potential by one

store max, 2nd max for chmin
if max <= x then return without doing anything
if x <= 2nd max then descend because we can decrease the potential
else 2nd max < x < max and we lazy set all occurrences of max to x

if no 2nd max then 2nd max is effectively -inf
store list at most 2 of maxes
setmax = -1 means no lazy
*/
const ll inf = 1e18;
struct Info {
    vl mx;
    pli mn = {inf, -1};
    void debug() {
        cerr << "mn: " << mn.first << " index " << mn.second << endl;
        cerr << "mx: ";
        for(auto x : mx) cerr << x << ",";
        cerr << endl;
    }
};
Info make(int idx, ll mn) {
    Info i;
    i.mx.push_back(mn);
    i.mn = {mn, idx};
    return i;
}
Info comb(Info a, Info b) {
    Info r;
    r.mn = min(a.mn, b.mn);
    r.mx.insert(end(r.mx), all(a.mx));
    r.mx.insert(end(r.mx), all(b.mx));
    sort(all(r.mx));
    r.mx.erase(unique(all(r.mx)), end(r.mx));
    reverse(all(r.mx));
    if(sz(r.mx) > 2) r.mx.resize(2);
    return r;
}
struct Node {
    int lo, hi;
    Node *l=0, *r=0;
    Info val;
    ll setmax = -1;
    Node(int lo, int hi) : lo(lo), hi(hi) {
        if(lo + 1 < hi) {
            int mid = lo + (hi - lo) / 2;
            l = new Node(lo, mid), r = new Node(mid, hi);
            val = comb(l->val, r->val);
        } else val = make(lo, lo == 0 ? 0 : inf);
    }
    void push() {
        if(!l) return;
        if(setmax == -1) return;
        l->chmin(lo, hi, setmax), r->chmin(lo, hi, setmax);
        setmax = -1;
    }
    void deactivate(int i) {
        if(lo+1 == hi) {
            val.mn = {inf, 1e6};
            val.mx = vl();
        } else {
            int mid = lo + (hi - lo) / 2;
            push();
            if(mid <= i) r->deactivate(i);
            else l->deactivate(i);
            val = comb(l->val, r->val);
        }
    }
    void debug() {
        cerr << "on [) " << lo << "," << hi << endl;
        cerr << "val: ";
        val.debug();
        if(l) push(), l->debug(), r->debug();
    }
    void chmin(int L, int R, ll x) {
        if(R <= lo || hi <= L) return;
        if(L <= lo && hi <= R) {
            // cerr << "chmin " << L << " " << R << " " << x << " on [) " << lo << "," << hi << endl;
            // cerr << "current: ";
            // val.debug();
            if(sz(val.mx) == 0 || val.mx[0] <= x) return;
            if(sz(val.mx) >= 2 && val.mx[1] >= x) {
                push();
                l->chmin(L, R, x), r->chmin(L, R, x);
                val = comb(l->val, r->val);
                return;
            }
            val.mx[0] = x;
            setmax = x;
            val.mn.first = min(val.mn.first, x);
            return;
        }
        push();
        l->chmin(L, R, x), r->chmin(L, R, x);
        val = comb(l->val, r->val);
    }
};


int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n; ll t; cin >> n >> t;
    t -= n-1;
    vl ps(n);
    rep(i, 1, n) {
        cin >> ps[i];
    }
    vl d(n);
    rep(i, 1, n-1) cin >> d[i];
    vector<pli> use;
    for(int i = n-1; i > 0; i--) {
        if(i == n-1 || use.back().first > ps[i]) use.push_back({ps[i], i});
    }
    // for(auto [p, i] : use) cerr << "range " << i << " cost " << p << endl;
    auto test = [&](int r) -> bool {
        // cerr << "testing range " << r << endl;
        Node tree(0, n);
        // tree.debug();
        while(tree.val.mn.first < inf) {
            auto [cur, i] = tree.val.mn;
            // cerr << "pop index " << i << " min val " << cur << endl;
            assert(i != -1);
            tree.deactivate(i);
            // tree.debug();
            cur += d[i];
            if(i == n-1) return cur <= t;
            int left = max(0, i - r);
            int right = min(n, i + r + 1);
            tree.chmin(left, right, cur);
        }
        return false;
    };
    int ans = -1;
    for(int dif = 1 << 20; dif; dif /= 2) {
        int cur = ans + dif;
        if(cur < sz(use) && test(use[cur].second)) {
            ans = cur;
            // cerr << "range " << use[cur].second << " worked" << endl;
        }
    }
    assert(ans != -1);
    cout << use[ans].first << "\n";
    // cerr << use[ans].second << "\n"


    return 0;
}
