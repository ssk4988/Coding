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

ll sum = 0, cnt = 0;
int n1, n2, k;
void calc(int prod, int left){
    if(left == 0){
        sum += prod;
        cnt++;
        return;
    }
    rep(i, n1, n2 + 1) calc(i * prod, left-1);
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cin >> n1 >> n2 >> k;
    calc(1, k);
    cout << (sum / ld(cnt)) << " " << sum << " " << cnt << nL;
    
    return 0;
}
