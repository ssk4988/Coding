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
        vi x(n);
        vi cnt(n);
        rep(i, 0, n) {
            cin >> x[i];
            x[i]--;
            cnt[x[i]]++;
        }
        int missing = -1;
        rep(i, 0, n) {
            if(cnt[i] == 0) missing = i;
        }
        if(missing != -1) {
            int a = missing == 0 ? 1 : 0;
            cout << "? " << missing+1 << " " << a+1 << endl;
            int q1; cin >> q1;
            cout << "? " << a+1 << " " << missing+1 << endl;
            int q2; cin >> q2;
            bool isA = q1 == 0 || q2 == 0;
            cout << "! " << (isA ? "A" : "B") << endl;
        } else {
            int a = min_element(all(x)) - begin(x);
            int b = max_element(all(x)) - begin(x);
            cout << "? " << b+1 << " " << a+1 << endl;
            int q1; cin >> q1;
            cout << "? " << a+1 << " " << b+1 << endl;
            int q2; cin >> q2;
            bool isA = !(min(q1, q2) >= n-1);
            cout << "! " << (isA ? "A" : "B") << endl;
        }
    }
    
    return 0;
}
