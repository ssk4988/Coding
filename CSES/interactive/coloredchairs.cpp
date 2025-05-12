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
    int l = 0, r = n-1;
    char lc, rc;
    cout << "? " << l+1 << endl;
    cin >> lc;
    cout << "? " << r+1 << endl;
    cin >> rc;
    if(lc == rc) {
        cout << "! " << r+1 << endl;
        return 0;
    }
    while(r-l > 1) {
        int mid = l + (r-l)/2;
        cout << "? " << mid+1 << endl;
        char mc; cin >> mc;
        if((lc == mc) == ((l&1)==(mid&1))) {
            l = mid;
            lc = mc;
        } else {
            r = mid;
            rc = mc;
        }
    }
    assert(lc == rc);
    cout << "! " << l+1 << endl;

    
    return 0;
}
