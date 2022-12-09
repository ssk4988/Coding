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
    char c1, c2;
    ll score = 0;
    int sc[3][3];
    rep(i, -1, 2){
        rep(j, 0, 3){
            sc[j][(j + 3 + i) % 3] = 3 + 3 * i;
        }
    }
    while((cin >> c1 >> c2) && c1 != '_'){
        score += sc[c1 - 'A'][c2 - 'X'];
        score += c2 - 'X' + 1;
    }
    cout << score << nL;
    
    return 0;
}