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
    int nc; 
    cin >> nc;
    rep(cn, 0, nc){
        int n, k1, k2; cin >> n >> k1 >> k2;
        int w, b; cin >> w >> b;
        int curW = 0, curB = 0;
        int cW = min(k1, k2), cB = min(n - k1, n - k2);
        curW = cW;
        curB = cB;
        curW += (k1 - cW) / 2;
        curW += (k2 - cW) / 2;
        curB += (n - k1 - cB) / 2;
        curB += (n - k2 - cB) / 2;
        if(curB >= b && curW >= w){
            cout << "YES\n";
        }
        else{
            cout << "NO\n";
        }
        
    }
    
    return 0;
}