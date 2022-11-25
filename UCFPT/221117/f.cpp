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
    int n;
    cin >> n;
    rep(i, 0, n){
        string str;cin >> str;
        int k = str.length();
        int sum = 0;

        rep(j, 0, k){
            int d = str[k - 1 - j] - '0';
            int d1 = j % 2 == 0 ? d : d * 2;
            d1 = d1 / 10 + d1 % 10;
            sum += d1;
        }
        cout << (sum % 10 == 0 ? "PASS" : "FAIL") << nL;
    }

    
    return 0;
}