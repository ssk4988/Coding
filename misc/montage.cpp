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
    vi h(n), v(n);
    rep(i, 0, n) cin >> h[i];
    rep(i, 0, n) cin >> v[i];
    if(h[0] > v[0]){
        cout << 0 << "\n";
        return 0;
    }
    int dif = v[0] - h[0]; // min answer
    bool tiebroken = false;
    rep(i, 1, n){
        if(v[i] - h[i] < dif){
            tiebroken = false;
            break;
        }
        if(v[i] - h[i] > dif){
            tiebroken = true;
            dif++;
            break;
        }
    }
    cout << dif << "\n";
    
    return 0;
}
