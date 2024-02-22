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

vi kmp(string str) {
    vi p(sz(str));
    rep(i, 1, sz(str)){
        int g = p[i-1];
        while(g && str[g] != str[i]) g = p[g - 1];
        p[i] = g + (str[g] == str[i]);
    }
    return p;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    // cin.exceptions(cin.failbit);
    string str;
    while(cin >> str){
        string revstr(str);
        reverse(all(revstr));
        vi p = kmp(revstr + '|' + str);
        int n = sz(str);
        int best = n - 2;
        rep(i, n+1, sz(p)){
            if(p[i]){
                if(i + p[i] == sz(p) || i + p[i] - 1 == sz(p)) best = min(best, i - (n+1) - p[i]);
            }
        }
        string clip = str.substr(0, best + 1);
        reverse(all(clip));
        cout << str << clip << endl;    
    }
    
    return 0;
}
