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

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    vii sets;
    int psum = 0;
    const int cnt = 13;
    rep(i, 1, 150) {
        int nc2 = i * (i+1) / 2;
        if(i == 1 || nc2 > psum) {
            sets.emplace_back(i, nc2);
            psum += nc2;
        }
    }
    // int sum = 0;
    // for(auto [a, b] : sets) {
    //     cerr << a << " " << b << endl;
    //     sum += 1 + a * 2;
    // }
    // cerr << "at a time: " << sz(sets) << " sum: " << sum << endl;
    map<int, int> ans;
    rep(mask, 0, 1 << cnt) {
        int sm = 0;
        rep(i, 0, cnt) {
            if((mask >> i)&1) sm += sets[i].s;
        }
        ans[sm] = mask;
    }
    assert(sz(ans) == (1 << cnt));
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        int n; cin >> n;
        vi state(n, -1);
        int pref = 0; // largest pref such that [0, pref) has no rbs
        for(int dif = 1 << 20; dif; dif /= 2) {
            int cur = pref + dif;
            if(cur > n) continue;
            cout << "? " << cur << " ";
            rep(i, 0, cur) {
                cout << i+1 << " ";
            }
            cout << endl;
            int res; cin >> res;
            if(res == 0) pref = cur;
        }
        int open = -1, close = -1;
        if(pref == n) {
            open = n-1, close = 0;
        } else open = pref-1, close = pref;
        state[open] = 0;
        state[close] = 1;
        if(n == 2) {
            cout << "! ";
            rep(i, 0, n) cout << "()"[state[i]];
            cout << endl;
            continue;
        }
        vi qs;
        rep(i, 0, n) {
            if(state[i] == -1) qs.pb(i);
        }
        while(sz(qs) % cnt != 0) qs.pb(qs.back());
        while(sz(qs)) {
            vi cands;
            rep(i, 0, cnt) {
                cands.pb(qs.back()); qs.pop_back();
            }
            int output = 0;
            cout << "? 829 ";
            rep(i, 0, cnt) {
                output++;
                cout << (open+1) << " ";
                rep(j, 0, sets[i].f) {
                    output++;
                    output++;
                    cout << (open+1) << " " << cands[i]+1 << " ";
                }
            }
            assert(output == 829);
            cout << endl;
            int res; cin >> res;
            assert(ans.count(res));
            int mask = ans[res];
            rep(i, 0, cnt) {
                state[cands[i]] = (mask >> i)&1;
            }
        }
        cout << "! ";
        rep(i, 0, n) {
            assert(state[i] != -1);
            cout << "()"[state[i]];
        }
        cout << endl;
    }
    
    return 0;
}
