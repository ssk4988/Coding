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
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n; cin >> n;
        vi a(n);
        set<int> left, right;
        rep(i, 0, n){
            cin >> a[i];
        }
        rep(i, 1, n){
            // left[i] = (a[i] == a[i-1] ? left[i-1] : i-1);
            if(a[i] != a[i-1]) left.insert(i);
        }
        for(int i = n- 2; i >= 0; i--){
            // right[i] = (a[i] == a[i+1] ? right[i+1] : i+1);
            if(a[i] != a[i+1]) right.insert(i);
        }
        int q; cin >> q;
        rep(i, 0, q){
            int l, r; cin >> l >> r; l--, r--;
            auto it = left.upper_bound(l);
            if(it != left.end() && *it <= r){
                cout << (*it - 1 + 1) << " " << (*it + 1) << "\n";
                continue;
            }
            it = right.lower_bound(r);
            if(it != right.begin() && *prev(it) >= l){
                it = prev(it);
                cout << (*it + 1) << " " << (*it + 1 + 1) << "\n";
                continue;
            }
            cout << "-1 -1\n";
        }
    }
    
    return 0;
}
