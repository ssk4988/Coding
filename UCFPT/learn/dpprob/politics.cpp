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
    int n; cin >> n;
    vi t(n), a(n), b(n);
    int siz = 2'500'000;
    vector<ld> e(siz), suff(siz);
    rep(i, 0, n){
        cin >> t[i] >> a[i] >> b[i];
    }
    int point = n - 1;
    for(int i = siz - 1; i >= 0; i--){
        while(point >= 0 && t[point] == i){
            int start = t[point] + a[point];
            int end = t[point] + b[point];
            e[i] = max(e[i], 1 + (suff[start] - suff[end + 1])/(b[point] - a[point] + 1));
            point--;
        }
        if(i + 1 < siz){
            e[i] = max(e[i], e[i + 1]);
        }
        suff[i] = e[i] + (i + 1 < siz ? suff[i + 1] : 0);
    }
    cout << e[0] << nL;

    
    return 0;
}
