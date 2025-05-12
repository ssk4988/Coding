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
        cout << "Case " << cn+1 << ":\n";
        int n; cin >> n;
        vi last(186);
        rep(i, 1, n+1) {
            int r; cin >> r;
            rep(j, 0, r) {
                int k; cin >> k;
                rep(l, 0, k) {
                    int v; cin >> v; v--;
                    last[v] = i;
                }
            }
            rep(j, 0, 186) {
                if(i - last[j] >= 10) {
                    cout << "Day " << i+1 << ": Full Search " << j+1 << "\n";
                } else if(i - last[j] >= 4) {
                    cout << "Day " << i+1 << ": Extra Ranger " << j+1 << "\n";
                }
            }
        }
    }
    
    return 0;
}
