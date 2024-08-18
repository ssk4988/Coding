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
    auto solve = [](int nzero) -> int {
        switch(nzero % 4){
            case 1:
            case 2:
            case 3:
                return -1; // lose
            case 0:
                return -1; // draw
        }
        return 0;
    };
    rep(cn, 0, nc){
        int n; cin >> n;
        string s; cin >> s;
        int nzero = 0;
        for(char c : s){
            if(c == '0') nzero++;
        }
        if(nzero == 0){
            cout << "DRAW\n";
            continue;
        }
        int ans = 0;
        if(n & 1){
            if(s[n / 2] == '0'){ 
                if(nzero == 1){
                    ans = -1;
                }
                else{
                    nzero--; 
                    ans = -1 * solve(nzero); 
                }
            }
            else ans = solve(nzero);
        }
        else ans = solve(nzero);
        if(ans == 0) cout << "DRAW\n";
        else if(ans == 1) cout << "ALICE\n";
        else cout << "BOB\n";
    }
    
    return 0;
}