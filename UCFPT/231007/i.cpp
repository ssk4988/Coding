#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pi = pair<int, int>;
using pl = pair<ll, ll>;
using pd = pair<ld, ld>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vpi = vector<pi>;
using vpl = vector<pl>;
using vpd = vector<pd>;
using vvi = vector<vi>;

#define f first
#define s second
#define mp make_pair
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define nL "\n"

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    cout << "? " << n << " ";
    rep(i, 0, n) cout << (i + 1) << " ";
    cout << endl;
    int k; cin >> k;
    vi a(k);
    rep(i, 0, k) cin >> a[i];
    cout << "? " << n << " ";
    rep(i, 0, n) cout << ((n - 1 - i) + 1) << " ";
    cout << endl;
    vi a1(k);
    int k1; cin >> k1;
    assert(k1 == k);
    rep(i, 0, k) cin >> a1[i];
    int l = 0, r = k - 1;
    cout << "! ";
    rep(i, 0, n){
        int len = 1;
        while(a1[r] != a[l]){
            len++;
            r--;
        }
        cout << len << " ";
        rep(j, 0, len){
            cout << a[l + j] << " ";
        }
        l += len;
        r--;
    }
    cout << endl;
    return 0;
}