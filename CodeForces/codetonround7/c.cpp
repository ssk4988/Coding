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
        int n, x; cin >> n >> x;
        vpi a(n);
        vi b(n);
        multiset<int> bs;
        rep(i, 0, n){
            cin >> a[i].f;
            a[i].s = i;
        }
        rep(i, 0, n){
            int p; cin >> p;
            bs.insert(p);
        }
        bool works = true;
        sort(all(a));
        reverse(all(a));
        for(int i = x - 1; i >= 0; i--){
        // rep(i, 0, x){
            auto it = bs.begin();
            if(*it >= a[i].f) {
                works = false;
                break;
            }
            b[a[i].s] = *it;
            bs.erase(it);
        }
        rep(i, x, n){
            if(!works) break;
            auto it = bs.lower_bound(a[i].f);
            if(it == bs.end()){
                works = false;
                break;
            }
            b[a[i].s] = *it;
            bs.erase(it);
        }
        if(works){
            cout << "YES\n";
            rep(i, 0, n){
                cout << b[i] << " ";
            }
            cout << "\n";
        }
        else{
            cout << "NO\n";
        }
    }
    return 0;
}
