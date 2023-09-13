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
    rep(i, 0, n){
        int l, r; cin >> l >> r;
        if(l == r && l == 1){
            cout << "1\n";
            continue;
        }
        int len = r - l + 1;
        int numevens = len / 2 + (len % 2 == 1 && l % 2 == 0), numodds = len - numevens;
        if(numevens > numodds || len == 1) cout << "-1\n";
        else{
            vi ans(len);
            int start = len % 2 == 0 ? 0 : 3;
            if(len % 2 == 1){
                ans[0] = l + 1;
                ans[1] = l + 2;
                ans[2] = l;
            }
            for(int i = start; i < len; i += 2){
                ans[i] = i + l + 1;
                ans[i + 1] = i + l;
            }
            rep(i, 0, len) assert(__gcd(l + i, ans[i]) == 1);
            for(int i : ans) cout << i << " ";
            cout << nL;
        }
    }
    
    return 0;
}