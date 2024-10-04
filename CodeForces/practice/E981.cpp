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

const int N = 1e4 + 10;
using bs = bitset<N>;

struct Knapsack {
    vector<bs> k;
    Knapsack() {
        k.push_back({});
        k[0][0] = 1;
    }
    void add(int x) {
        k.push_back(k.back() | (k.back() << x));
    }
    void rollback(int t) {
        while(sz(k) > t) k.pop_back();
    }
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, q; cin >> n >> q;
    Knapsack k;
    vector<array<int, 3>> qs(q);
    rep(i, 0, q){
        rep(j, 0, 3) cin >> qs[i][j];
        qs[i][0]--;
    }
    bs ans;
    ans[0] = 1;
    auto go = [&](vector<array<int, 3>> cur, int L, int R, auto &&go) -> void {
        int t = sz(k.k);
        vector<array<int, 3>> keep;
        for(auto [l, r, x] : cur) {
            if (R <= l || r <= L) continue;
            keep.push_back({l, r, x});
        }
        swap(keep, cur);
        keep.clear();
        for(auto [l, r, x] : cur) {
            if (l <= L && R <= r) k.add(x);
            else keep.push_back({l, r, x});
        }
        swap(keep, cur);
        keep.clear();
        if(R-L == 1) {
            ans |= k.k.back();
            k.rollback(t);
            return;
        }
        int M = L + (R-L) / 2;
        go(cur, L, M, go);
        go(cur, M, R, go);
        k.rollback(t);
    };
    go(qs, 0, n, go);
    vi res;
    rep(i, 1, n+1){
        if(ans[i]) res.pb(i);
    }
    cout << sz(res) << "\n";
    for(int i : res) cout << i << " ";
    cout << "\n";
    return 0;
}
