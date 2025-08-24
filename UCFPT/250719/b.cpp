#include <bits/stdc++.h>
using namespace std;


using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;
using ll = long long;
using vl = vector<ll>;

#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int)x.size()

#define f first
#define s second

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    // using iter = map<int, int>::iterator;
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        int n, k; cin >> n >> k;
        map<int, int> a;
        rep(i, 0, n) {
            cin >> a[i];
        }
        vector<array<int, 3>> ans;
        set<pair<int, pii>> cnt;
        map<pii, set<int>> pairs;
        auto getkey = [&](int it) { return pii{-a[it], -next(a.find(it))->s}; };
        auto addpair = [&](int it) -> void { 
            auto key = getkey(it);
            cnt.erase({sz(pairs[key]), key}); 
            pairs[key].insert(it);
            cnt.insert({sz(pairs[key]), key});
        };
        auto rempair = [&](int it) -> void {
            auto key = getkey(it);
            cnt.erase({sz(pairs[key]), key}); 
            pairs[key].erase(it);
            cnt.insert({sz(pairs[key]), key});
        };
        auto upd = [&](int i, int x) -> void {
            auto it = a.find(i);
            int prv = -1, nxt = -1;
            if(it != begin(a)) {
                prv = prev(it)->f;
                rempair(prv);
            }
            if(next(it) != end(a)) {
                nxt = next(it)->f;
                rempair(i);
            }
            a[i] = x;
            if(prv != -1) addpair(prv);
            if(nxt != -1) addpair(i);
        };
        auto rem = [&](int i) -> void {
            // cerr << "calling rem on " << i << endl;
            auto it = a.find(i);
            int prv = -1, nxt = -1;
            if(it != begin(a)) {
                prv = prev(it)->f;
                rempair(prv);
            }
            if(next(it) != end(a)) {
                nxt = next(it)->f;
                rempair(i);
            }
            a.erase(i);
            if(prv != -1 && nxt != -1) addpair(prv);
        };
        rep(i, 0, n-1) {
            addpair(i);
        }
        rep(i, 1, k+1) {
            // cerr << "a: ";
            // for(auto [i, v] : a) cerr << i << "=" << v << " ";
            // cerr << endl;
            while(sz(cnt)) {
                auto it = rbegin(cnt);
                if(it->s.f == it->s.s) {
                    cnt.erase(prev(end(cnt)));
                } else break;
            }
            if(sz(cnt) == 0) break;
            auto [q, key] = *rbegin(cnt);
            if(q < 2) break;
            cnt.erase(prev(end(cnt)));
            vi v(all(pairs[key]));
            assert(sz(v) == q);
            ans.push_back({q, -key.f, -key.s});
            for(int cur : v) {
                // cerr << "occurrence at left is " << cur << endl;
                auto it = a.find(cur);
                assert(it != end(a) && next(it) != end(a));
                int nxt = next(a.find(cur))->f;
                rem(nxt);
                upd(cur, 255 + i);
            }
        }
        cout << sz(ans) << "\n";
        for(auto [q, b, c] : ans) {
            cout << b << " " << c << " " << q << "\n";
        }
        for(auto [i, v] : a) {
            cout << v << " ";
        }
        cout << "\n";
    }
    
    return 0;
}
