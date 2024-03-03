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
    vl a(n);
    rep(i, 0, n){
        cin >> a[i];
    }
    if(n == 1){
        cout << "1 1\n";
        cout << -a[0] << "\n";
        cout << "1 1\n";
        cout << 0 << "\n";
        cout << "1 1\n";
        cout << 0 << "\n";
        return 0;
    }
    int len = (n+1)/2;
    rep(i, len, n+1){
        if(__gcd(i, n) == 1){
            len = i;
            break;
        }
    }
    assert(__gcd(len, n) == 1);
    vi times(n);
    rep(i, 0, n){
        times[(ll(len) * i) % n] = i;
    }
    cout << 1 << " " << len << "\n";
    rep(i, 0, len){
        cout << (times[(a[i] % n + n) % n] * ll(-len)) << " ";
        a[i] += (times[(a[i] % n + n) % n] * ll(-len));
    }
    cout << "\n";
    cout << (n - len + 1) << " " << n << "\n";
    rep(i, n - len, n){
        cout << (times[(a[i] % n + n) % n] * ll(-len)) << " ";
        a[i] += (times[(a[i] % n + n) % n] * ll(-len));
    }
    cout << "\n";
    cout << 1 << " " << n << "\n";
    rep(i, 0, n){
        assert((a[i] % n + n) % n == 0);
        cout << -a[i] << " ";
    }
    cout << "\n";
    return 0;
}