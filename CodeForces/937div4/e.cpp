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
        string s; cin >> s;
        int ans = n;
        rep(len, 1, n){
            if(n % len != 0) continue;
            int diff = 0;
            rep(i, 0, len){
                vi freq(26);
                for(int j = i; j < n; j += len){
                    freq[s[j] - 'a']++;
                }
                int cnt = 0;
                vi c;
                rep(j, 0, 26){
                    if(freq[j]){
                        cnt++;
                        c.pb(freq[j]);
                    }
                }
                if(cnt > 2) diff = 1e9;
                if(cnt == 1) continue;
                if(c[0] == 1 || c[1] == 1) diff++;
                else diff = 1e9;
            }
            if(diff <= 1) ans = min(ans, len);
        }
        cout << ans << "\n";
    }
    
    return 0;
}