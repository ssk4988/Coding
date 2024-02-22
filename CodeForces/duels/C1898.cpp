#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pi = pair<int, int>;
using pl = pair<ll, ll>;
using pd = pair<ld, ld>;
// using vi = vector<int>;
using vi = vector<bool>;
using vl = vector<ll>;
using vd = vector<ld>;
using vpi = vector<pi>;
using vpl = vector<pl>;
using vpd = vector<pd>;
// using vvi = vector<vi>;
using vvi = vector<vector<bool>>;

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
        int n, m, k; cin >> n >> m >> k;
        if(k < (n-1) + (m-1) || (k & 1) != ((n-1+m-1)&1)){
            cout << "NO\n";
            continue;
        }
        cout << "YES\n";
        vvi horiz(n, vi(m-1));
        vvi vert(n-1, vi(m));
        bool blue = false;
        rep(i, 0, n-1){
            vert[i][0] = blue;
            blue = !blue;
        }
        rep(i, 0, m-1){
            horiz[n-1][i] = blue;
            blue = !blue;
        }
        horiz[n-2][m-2] = horiz[n-1][m-2];
        vert[n-2][m-1] = vert[n-2][m-2] = !horiz[n-1][m-2];
        vert[0][1] = true;
        for(auto &v : horiz){
            for(auto x : v){
                cout << (x ? "B" : "R") << " ";
            }
            cout << nL;
        }
        for(auto &v : vert){
            for(auto x : v){
                cout << (x ? "B" : "R") << " ";
            }
            cout << nL;
        }
    }

    
    return 0;
}
