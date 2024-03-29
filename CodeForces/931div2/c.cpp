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
#define all(r) r.begin(), r.end()
#define sz(r) (int)(r).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define nL "\n"

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n, m; cin >> n >> m;
        cout << "? " << 1 << " " << 1 << endl;
        int res1, res2, res3; cin >> res1;
        cout << "? " << 1 << " " << m << endl;
        cin >> res2;
        // r + c = res1
        // c - r = m-1 - res2
        // c = (m-1 + res1 - res2) / 2;
        if(((m-1) + res1 - res2) % 2 == 0){
            int c = ((m-1) + res1 - res2) / 2;
            int r = res1 - c;
            if(c >= 0 && c <= m-1 && r >= 0 && r <= n-1){
                cout << "? " << (r+1) << " " << (c+1) << endl;
                int res4; cin >> res4;
                if(res4 == 0){
                    cout << "! " << (r+1) << " " << (c+1) << endl;
                    continue;
                }
            }
        }
        cout << "? " << n << " " << m << endl;
        cin >> res3;
        // r + c = n-1 + m-1 - res3
        // c - r = m-1 - res2
        // c = (n-1+m-1+m-1 - res3 - res2) / 2
        int c = (n-1+m-1+m-1 - res3 - res2);
        assert(c % 2 == 0);
        c /= 2;
        int r = n-1 + m-1 - res3 - c;
        assert(c >= 0 && c <= m-1 && r >= 0 && r <= n-1);
        cout << "! " << (r+1) << " " << (c+1) << endl;
    }
    
    return 0;
}

// tests: n=4 m=5 4,2 3,4
// 4 4
// 2 3
// 3 2
// 5 4
// 1 1
// 5 4
