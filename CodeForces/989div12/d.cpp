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
using vll = vector<pll>;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

void solve(int cn) {
    int n; cin >> n;
    vi a(n);
    vector<set<int>> idxs(3);
    rep(i, 0, n){
        cin >> a[i];
    }
    vi b(a);
    sort(all(b));
    vi start(3, -1);
    rep(i, 0, n){
        if(start[b[i]] == -1) start[b[i]] = i;
    }
    vii moves;
    int l = 0, r = n-1;
    auto add = [&](int i) -> void {
        if(a[i] != b[i]) idxs[a[i]].insert(i);
    };
    auto rem = [&](int i) -> void {
        if(idxs[a[i]].count(i)) idxs[a[i]].erase(i);
    };
    auto sw = [&](int i, int j) -> void {
        assert(abs(a[i] - a[j]) == 1);
        rem(i);
        rem(j);
        // idxs[a[i]].erase(i);
        // idxs[a[j]].erase(j);
        swap(a[i], a[j]);
        moves.pb({i, j});
        add(i);
        add(j);
        // idxs[a[i]].insert(i);
        // idxs[a[j]].insert(j);
    };
    rep(i, 0, n){
        add(i);
    }
    while(l < r) {
        if(a[l] == b[l] || a[r] == b[r]){
            while(l < r && a[l] == b[l]) {
                // idxs[a[l]].erase(l);
                rem(l);
                l++;
            }
            while(l < r && a[r] == b[r]) {
                // idxs[a[r]].erase(r);
                rem(r);
                r--;
            }
            continue;
        }
        if((a[l] == b[r] || a[r] == b[l]) && abs(a[l] - a[r]) == 1) {
            sw(l, r);
        } else if(a[l] == a[r]) {
            assert(a[l] == 1 && a[r] == 1);
            assert(b[l] == 0);
            assert(sz(idxs[0]));
            int id = *idxs[0].begin();
            sw(l, id);
        } else {
            assert(a[l] == 2 && a[r] == 0);
            // assert(sz(idxs[1]));
            int id = start[1];
            if(sz(idxs[1])) id = *idxs[1].begin();
            // int id = *idxs[1].begin();
            sw(l, id);
            id = l;
            while(a[id] != b[id]){
                int nid = (b[id] == 0 ? *idxs[0].rbegin() : *idxs[2].begin());
                sw(id, nid);
                id = nid;
            }
            // sw(l, r);
            // sw(r, id);
        }
    }
    assert(is_sorted(all(a)));
    assert(sz(moves) <= n);
    cout << sz(moves) << "\n";
    for(auto [i, j] : moves){
        cout << i+1 << " " << j+1 << "\n";
    }
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        solve(cn);
    }
    
    return 0;
}
