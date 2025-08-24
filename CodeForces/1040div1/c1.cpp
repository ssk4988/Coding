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
        while(sz(qs) % 2 == 1) qs.pb(qs.back());
        for(int i = 0; i < sz(qs); i += 2) {
            int a = qs[i], b = qs[i+1];
            cout << "? 6 ";
            cout << (open+1) << " " << (a+1) << " " << (open+1) << " " << (a+1) << " ";
            cout << (open+1) << " " << (b+1) << endl;
            int res; cin >> res;
            if(res == 0) state[a] = state[b] = 0;
            else if(res == 1) state[a] = 0, state[b] = 1;
            else if(res == 3) state[a] = 1, state[b] = 0;
            else state[a] = state[b] = 1;
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
