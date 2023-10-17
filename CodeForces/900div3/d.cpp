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
        int n, k; cin >> n >> k;
        string str; cin >> str;
        vi l(k), r(k);
        rep(i, 0, k){
            cin >> l[i];
            l[i]--;
        }
        rep(i, 0, k){
            cin >> r[i];
            r[i]--;
        }
        vi flp(n);
        int q; cin >> q;
        rep(i, 0, q){
            int x; cin >> x;
            x--;
            int idx = upper_bound(all(l), x) - l.begin() - 1;
            int l1 = min(x, l[idx] + r[idx] - x), r1 = max(x, l[idx] + r[idx] - x);
            flp[l1] ^= 1;
            // if(r1 + 1 < n) flp[r1 + 1] ^= 1;
        }
        rep(j, 0, k){
            int pref = 0;
            int mid = l[j] + (r[j] - l[j] + 1) / 2;
            rep(i, l[j], mid){
                pref ^= flp[i];
                if(pref){
                    swap(str[i], str[l[j] + r[j] - i]);
                }
            }

        }
        cout << str << nL;
    }
    
    return 0;
}
