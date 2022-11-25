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

vector<int> prefix_function(string s) {
    int n = (int)s.length();
    vector<int> pi(n);
    for (int i = 1; i < n; i++) {
        int j = pi[i-1];
        while (j > 0 && s[i] != s[j])
            j = pi[j-1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
    return pi;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc;
    cin >> nc;
    string str1, str2;
    rep(cn, 0, nc){
        cin >> str1 >> str2;
        int tn = str2.length();
        vi prefpi = prefix_function(str2);
        vi prefcnt(tn, 1);
        prefcnt[tn - 1] = 0;
        rep(i, 0, tn){
            if(prefpi[i] == 0) continue;
            prefcnt[i] += prefcnt[prefpi[i] - 1];
        }
        vi fmatch = prefix_function(str2 + "#" + str1);
        reverse(all(str2));
        reverse(all(str1));
        vi suffpi = prefix_function(str2);
        vi suffcnt(tn, 1);
        suffcnt[tn - 1] = 0;
        rep(i, 0, tn){
            if(suffpi[i] == 0) continue;
            suffcnt[i] += suffcnt[suffpi[i] - 1];
        }
        vi rmatch = prefix_function(str2 + "#" + str1);
        int offset = tn + 1;
        reverse(rmatch.begin() + offset, rmatch.end());
        ll ans = 0;
        rep(i, 0, str1.size() - 1){
            if(fmatch[offset + i] <= 0 || rmatch[offset + i + 1] <= 0) continue;
            ans += (ll)prefcnt[fmatch[offset + i]-1] * suffcnt[rmatch[offset + i + 1]-1];
        }
        cout << "Case " << (cn + 1) << ": " << ans << nL;
    }
    
    return 0;
}