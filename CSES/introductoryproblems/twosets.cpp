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
    ll sum = ll(n) * (n + 1) / 2;
    if(sum % 2 == 0){
        cout << "YES" << nL;
        vi used(n + 1);
        ll rem = sum / 2;
        int cnt = 0;
        for(int i = n; i > 0; i--){
            if(rem >= i){
                used[i] = true;
                rem -= i;
                cnt++;
            }
        }
        cout << cnt << nL;
        rep(i, 1, n + 1) if(used[i]) cout << i << " ";
        cout << nL;
        cout << (n - cnt) << nL;
        rep(i, 1, n + 1) if(!used[i]) cout << i << " ";
        cout << nL;
    }
    else{
        cout <<"NO" << nL;
    }
    
    return 0;
}
