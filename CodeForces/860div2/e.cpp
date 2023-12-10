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
        rep(i, 0, n) cin >> a[i];
        vector<array<int, 3>> jmp(n + 1); // jump to, length, max lengthen
        int maxlen = 0;
        jmp[n] = {n, 0, 0};
        for(int i = n - 1; i >= 0; i--){
            int nex = i + a[i] + 1;
            if(nex > n){
                jmp[i] = {nex, 1, maxlen + 1};
            }
            else jmp[i] = {jmp[nex][0], jmp[nex][1] + 1, max(maxlen, jmp[nex][2]) + 1};
            if(jmp[i][0] == n) maxlen = max(maxlen, jmp[i][1]);
        }
        rep(i, 0, n - 1){
            int ans = 2;
            if(jmp[i + 1][0] == n){
                if(jmp[i + 1][1] == a[i]) ans = 0;
                else ans = 1;
            }
            else if(max(jmp[i + 1][1], jmp[i + 1][2]) >= a[i]){
                ans = 1;
            }
            cout << ans << " ";
        }
        cout << nL;
    }
    
    return 0;
}
