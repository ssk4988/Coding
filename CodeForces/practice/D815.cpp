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

const int LIM = 5e5 + 100;
const int inf = 1e9;
struct Node
{
    Node *l = 0, *r = 0;
    int lo, hi;
    ll sum = 0, mx = 0, mn = 0, lzmax = 0;

    // , mset = inf, madd = 0, val = -inf;
    Node(int lo, int hi) : lo(lo), hi(hi)
    {
        if (lo + 1 < hi)
        {
            int mid = lo + (hi - lo) / 2;
            l = new Node(lo, mid);
            r = new Node(mid, hi);
            mx = max(l->mx, r->mx);
            mn = min(l->mn, r->mn);
            sum = l->sum + r->sum;
        }
    }
    ll query()
    {
        return sum;
    }
    // int query(int L, int R) {
    // 	if (R <= lo || hi <= L) return -inf;
    // 	if (L <= lo && hi <= R) return val;
    // 	push();
    // 	return max(l->query(L, R), r->query(L, R));
    // }
    void set(int L, int R, ll x)
    {
        if (R <= lo || hi <= L)
            return;
        if (L <= lo && hi <= R)
        {
            lzmax = mx = mn = x;
            sum = x * (hi - lo);
        }
        else if(lo + 1 < hi)
        {
            push();
            l->set(L, R, x), r->set(L, R, x);
            mx = max(l->mx, r->mx);
            mn = min(l->mn, r->mn);
            sum = l->sum + r->sum;
        }
    }
    void chmax(int L, int R, ll x){
        if (R <= lo || hi <= L)
            return;
        if (L <= lo && hi <= R){
            if(mx < x){
                set(L, R, x);
            }
            else{
                push();
                if(lo + 1 != hi){
                    if(l->mn < x)l->chmax(L, R, x);
                    if(r->mn < x)r->chmax(L, R, x);
                    mx = max(l->mx, r->mx);
                    mn = min(l->mn, r->mn);
                    sum = l->sum + r->sum;
                }
            }
        }else{
            push(), l->chmax(L, R, x), r->chmax(L, R, x);
            mx = max(l->mx, r->mx);
            mn = min(l->mn, r->mn);
            sum = l->sum + r->sum;
        }
    }
    void push()
    {
        if(lzmax != 0 && lo + 1 < hi){
            l->set(lo, hi, lzmax);
            r->set(lo, hi, lzmax);
            lzmax = 0;
        }
    }
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    ll n, p, q, r;
    cin >> n >> p >> q >> r;
    vector<array<int, 3>> cs(n);
    rep(i, 0, n)
    {
        rep(j, 0, 3)
        {
            cin >> cs[i][j];
        }
    }
    ll ans = 0;
    // sort(all(cs));
    vector<vpi> v(p + 1);
    Node tree(1, q + 1);
    for (auto [v0, v1, v2] : cs)
    {
        tree.chmax(1, v1 + 1, v2);
        v[v0].pb({v1, v2});
    }
    for(int v0 = p; v0 >= 1; v0--){
        for(auto [v1, v2] : v[v0]){
            tree.set(1, v1 + 1, r);
            tree.chmax(v1 + 1, q + 1, v2);
        }
        ans += q * r - tree.query();
    }
    // ans = p * q * r - ans;
    cout << ans << nL;

    return 0;
}
