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
    int k = 0;
    while(3 * k + 1 < 2 * n) k++;
    if(n == 1){
        cout << "1\n1 1\n";
        return 0;
    }
    if(n == 2){
        cout << "1\n1 1\n";
        return 0;
    }
    int p2 = (n-2)/3*3+2;
    int k1 = (2 * p2 - 1) / 3;
    int v1 = (k1+1)/2;
    // cout << n << " " << p2 << " " << k1 << " " << v1 << endl;
    vpi v;
    rep(i, 0, v1) {
        v.pb({i, v1-1-i});
    }
    k1 = k1 - v1;
    rep(i, 0, k1) {
        v.pb({p2-1-i, p2-1-(k1-1-i)});
    }
    rep(i, 0, n-p2){
        v.pb({p2+i, p2+i});
    }
    cout << sz(v) << "\n";
    for(auto [x, y] : v){
        cout << x+1 << " " << y+1 << "\n";
    }
    

    
    return 0;
}
