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
bool coprime[100005];

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n;
    cin >> n;
    memset(coprime, true, sizeof coprime);
    int cnt = 1;
    ll mod = 1;
    rep(i, 2, n)
    {
        if (coprime[i] && n % i == 0)
        {
            for (int j = i; j < n; j += i)
            {
                coprime[j] = false;
            }
        }
        if (coprime[i])
        {
            mod = (mod * i) % n;
            cnt++;
        }
    }
    if(mod != 1){
        cnt--;
        coprime[mod]=false;
    }
    cout << cnt << nL;
    rep(i, 1, n){
        if(coprime[i]){
            cout << i << " ";
        }
    }
    cout << nL;

    return 0;
}