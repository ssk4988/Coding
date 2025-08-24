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

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    srand(time(NULL));
    rep(i, 0, 100) {
        const ll mod = 1LL << 32;
        ll v = rand() % mod;
        if(v % 2 == 0) continue;
        cerr << v << endl;
        // ll cur = (v * v) & (mod-1);
        ll cur = v;
        ll p = 1;
        vl res;
        while(cur != 1) {
            // cerr << cur << " " << v << " " << p << endl;
            (cur *= v) &= (mod-1);
            p++;
        }
        cur = 1;
        int cnt = 0;
        rep(p2, 0, p) {
            if((cur & (p-1)) == p2) {
                cnt++;
            }
            (cur *= v) &= (mod-1);
        }
        cur = v;
        ll p2 = 1;
        while(p2 <= p) {
            cerr << setw(10) << cur << " " << setw(10) << p2 << " " << bitset<32>(cur & (mod-1)) << endl;
            p2 *= 2;
            (cur *= cur) &= (mod-1);
        }
        cerr << "pow: " << p << " works: " << cnt << endl;

    }
    
    return 0;
}
