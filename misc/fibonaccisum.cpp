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

vi fib = {0, 1};
const int MOD = 1e9+7;
int calc(int x) {
    while(sz(fib) <= x) {
        fib.pb((fib.back() + fib[sz(fib) - 2]) % MOD);
    }
    return fib[x];
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    string s; cin >> s;
    int n = sz(s), pref = 0;
    int ans = 0;
    for(int i = 0; i < n; i++){
        if(s[i] == '1') {
            ans = ((ll)ans + calc(2 * (n - i - 1) + pref)) % MOD;
        }
        if(s[i] == '1') pref++;
    }
    ans = (ans + calc(pref)) % MOD;
    cout << ans << "\n";
    
    return 0;
}