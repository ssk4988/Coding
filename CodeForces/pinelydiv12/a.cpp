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
        int n, a, q; cin >> n >> a >> q;
        int cnt = a;
        int maxcnt = a;
        int add = 0;
        string str; cin >> str;
        rep(i, 0, q){
            if(str[i] == '+'){
                add++;
                cnt++;
                maxcnt = max(maxcnt, cnt);
            }
            else{
                cnt--;
            }
        }
        if(maxcnt == n){
            cout << "YES\n";
        }
        else if(maxcnt < n && a + add < n){
            cout << "NO\n";
        }
        else{
            cout << "MAYBE\n";
        }
    }
    
    return 0;
}
