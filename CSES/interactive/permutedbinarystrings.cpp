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
    vi a(n);
    rep(b, 0, 10) {
        cout << "? ";
        rep(i, 0, n){
            cout <<( (i >> b)&1);
        }
        cout << endl;
        string s; cin >> s;
        rep(i, 0, n){
            if(s[i] == '1') a[i] += 1 << b;
        }
    }
    cout << "! ";
    rep(i, 0, n) {
        cout << a[i]+1 << " ";
    }
    cout << endl;
    return 0;
}
