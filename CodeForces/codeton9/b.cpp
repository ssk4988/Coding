#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vii = vector<pii>;
using vll = vector<pll>;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        string s; cin >> s;
        bool works = false;
        int n = sz(s);
        for(int i = 0; i < n; i++){
            if(i + 1 < n && s[i] == s[i+1]){
                works= true;
                cout << s.substr(i,2) << "\n";
                break;
            }
            if(i + 2 < n && s[i] != s[i+1] && s[i] != s[i+2] && s[i+1] != s[i+2]){
                works = true;
                cout << s.substr(i,3) << "\n";
                break;
            }
        }
        if(!works){
            cout << "-1\n";
        }
    }
    
    return 0;
}
