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
string printlen(int a, int l) {
    string s;
    rep(i, 0, l) {
        s.push_back('0' + ((a >> i)&1));
    }
    reverse(all(s));
    return s;
}
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    const int L = 11;
    map<array<int, 3>, int> masks;
    rep(l, 3, L+1) {
        int l2 = l-3;
        rep(mask, 0, 1 << l) {
            int q1 = 0;
            rep(i, 0, l) {
                if((mask >> i) & 1) {
                    q1 += (i+1) * (l-i);
                }
            }
            int q2 = 0;
            rep(i, 0, l2) {
                if((mask >> i) & 1) {
                    q2 += (i+1) * (l2 - i);
                }
            }
            array<int, 3> key{l, q1, q2};
            if(masks.count(key)) {
                cout << "collision at l=" << l << " mask1=" << printlen(masks[key], l) << " mask2=" << printlen(mask, l) << "\n";
            }
            masks[key] = mask;
        }
    }
    
    
    return 0;
}
