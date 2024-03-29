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
    while(true){
        int n; cin >> n;
        if(n == 42) break;
        vector<string> ans;
        auto go = [&](string &str, int sum, auto &&go) -> void {
            if(sum > 42) return;
            if(sz(str) == n){
                if(sum == 42){
                    swap(str[n-2], str[n-1]);
                    ans.pb(str);
                    swap(str[n-2], str[n-1]);
                }
                return;
            }
            rep(i, 'a', sz(str) == 0 ? ('z' + 1) : str.back()){
                if(i == 'a' || i == 'e' || i == 'i' || i == 'o' || i == 'u' || i == 'y') continue;
                str.pb(i);
                go(str, sum + i - 'a' + 1, go);
                str.pop_back();
            }
        };
        string str;
        go(str, 0, go);
        // cout << sz(ans) << "\n";
        sort(all(ans));
        cout << "XKCD-like name(s) of length: " << n << "\n";
        for(auto s : ans) cout << s << nL;
        if(sz(ans) == 0) cout << "Mostly Harmless\n";
    }
    cout << "The answer to life, the universe and everything!\n";
    
    return 0;
}
