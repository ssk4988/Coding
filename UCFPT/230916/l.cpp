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
    string str;
    cin >> str;
    int n = sz(str);
    int rot = 0, bal = 0;
    rep(i, 0, n - 1){
        bal += (str[i] == '(' ? 1 : -1);
        if(bal == 0){
            rot = i + 1;
            break;
        }
    }
    string str1(str);
    rotate(str1.begin(), str1.begin() + rot, str1.end());
    if(str1 == str){
        cout << "no\n";
    }
    else{
        cout << str1 << nL;
    }

    return 0;
}
