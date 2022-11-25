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
        string str1, str2;
        cin >> str1 >> str2;
        str1 += str1;
        bool works = str1.find(str2) != -1;
        reverse(all(str1));
        works |= str1.find(str2) != -1;
        works &= str1.length() == str2.length() * 2;
        cout << "Case #" << (i + 1) << ": " << (works ? "YES" : "NO") << nL;
    }
    
    return 0;
}