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

const int N = 2e5+10;
int ops[N];
vector<pair<ll, int>> freqs[N];

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        int n; cin >> n;
        rep(i, 0, n) {
            ops[i] = 0;
            freqs[i] = vector<pair<ll, int>>();
        }
        
        for(int i = n-1; i >= 0; i--) {
            ll a; cin >> a;
            int k; cin >> k;
            vi children(k);

            rep(j, 0, k) {
                cin >> children[j]; children[j]--;
                int c = children[j];
                freqs[i].insert(end(freqs[i]), all(freqs[c]));
                freqs[c] = vector<pair<ll, int>>();
                ops[i] += ops[c];
            }
            sort(all(freqs[i]));
            vector<pair<ll, int>> un;
            ll l = 1;
            for(auto [b, f] : freqs[i]) {
                b = gcd(b, a);
                if(l % b == 0) continue;
                if(sz(un) && un.back().first == b) un.back().second += f;
                else un.push_back({b, f});
                l = lcm(l, b);
            }
            freqs[i] = un;
            if(sz(freqs[i]) == 0) {
                ops[i]++;
                freqs[i].push_back({a, 1});
            }
            cout << ops[i] << endl;
        }
    }    
    
    return 0;
}
