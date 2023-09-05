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
        int n, m; cin >> n >> m;
        vi places(4, m);
        vector<char> cs = {'v', 'i', 'k', 'a'};
        vector<string> vs(n);
        rep(i, 0, n) cin >> vs[i];
        int st = 0;
        int cnt = 0;
        rep(i, 0, 4){
            bool found = false;
            rep(j, st, m){
                rep(k, 0, n){
                    if(vs[k][j] == cs[i]){
                        found = true;
                        st = j + 1;
                        cnt++;
                        break;
                    }
                }
                if(found) break;
            }
            if(!found) break;
            // cout << "found " << st << nL;
        }
        if(cnt == 4){
            cout << "YES\n";
        }
        else cout << "NO\n";
    }
    
    return 0;
}
