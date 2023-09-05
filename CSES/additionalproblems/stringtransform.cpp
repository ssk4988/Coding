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
    // int n; cin >> n;
    // string str; cin >> str;
    // str.pb('#');
    // int n= sz(str);
    // vector<string> strs;
    // rep(i, 0, n){
    //     strs.pb(string(str));
    //     rotate(str.begin(), str.begin() + 1, str.end());
    // }
    // sort(all(strs));
    // for(string s : strs) cout << s.back();
    // cout << nL;
    string str; cin >> str;
    vi cnt(26);
    int n = sz(str);
    rep(i, 0, n){
        if(str[i] == '#') continue;
        cnt[str[i] - 'a']++;
    }
    vi start(26), seen(26);
    int v = 1;
    rep(i, 0, 26){
        start[i] = v;
        v += cnt[i];
    }
    vi a(n), b(n);
    rep(i, 0, n){
        if(str[i] == '#') {
            a[i] = 0;
        }
        else{
            a[i] = start[str[i] - 'a'] + seen[str[i] - 'a'];
            seen[str[i] - 'a']++;
        }
        // b[a[i]] = i;
    }
    rep(i, 0, n) b[a[i]] = i;
    // rep(i, 0, n) cout << i << " " << a[i] << " " << b[i] << nL;
    int c = b[0];
    sort(all(str));
    string ans;
    while(c != 0){
        // rep(i,0,26){
        //     if(start[i] <= c){
                ans.pb(str[c]);
        //         break;
        //     }
        // }
        c = b[c];
    }
    cout << ans << nL;


    return 0;
}
