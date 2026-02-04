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
    int n; cin >> n;
    auto query = [&](int l, int r) -> ll {
        cout << l+1 << " " << r+1 << endl;
        ll inv; cin >> inv;
        if(inv == 0) exit(0);
        return inv;
    };
    if(n == 1){
        query(0, 0);
    }
    // 
    vi ord{0};
    ll inv = query(0, 1);
    rep(i,1,n) {
        // for(int v : ord) cerr << v << " ";
        // cerr << endl;
        ll inv2 = query(0, i);
        if(1 < i-1) inv2 = query(1, i-1);
        ll invfront = i-1;
        ll dif = inv2 - inv - invfront; // delta due to i moving to front
        // adds below - above
        // dif = below - (i-below) = 2 * below - i
        ll below = (dif+i)/2;
        for(int &v : ord) {
            if(v >= below) {
                v++;
            }
        }
        ord.pb(below);
        swap(ord[0], ord.back());
        int minidx = 0;
        rep(j, 0, sz(ord)) {
            if(ord[j] < ord[minidx]) minidx = j;
        }
        if(minidx != 0) {
            inv2 = query(0, minidx);
            reverse(begin(ord), begin(ord)+minidx+1);
        }
        inv = inv2;
    }
    rep(i, 0, n) {
        int minidx = i;
        rep(j, i, n) {
            if(ord[j] < ord[minidx]) minidx = j;
        }
        if(minidx > i) query(i, minidx);
        reverse(begin(ord)+i, begin(ord)+minidx+1);
    }
    
    return 0;
}

// 5
// 0 2 3 4 1
// 2 0 3 4 1
// 0 2 3 4 1
