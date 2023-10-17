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

bool found = false;
vi a;
ll lim;
int explored = 0;
void bt(int sum, ll prod, int mx){
    if(found) return;
    explored++;
    // if(sz(a) && a[0] > 30){
    //     for(int i : a) cout << i << " ";
    //     cout << nL;
    // }
    if(prod == lim && sum == 41){
        found = true;
        return;
    }
    
    if(sz(a) >= 100) return;
    for(int i = mx; i >= 1 && !found; i--){
        if(sum + i > 41 || prod * i > lim) continue;
        a.pb(i);
        bt(sum + i, prod * i, i);
        if(!found){
            a.pop_back();
        }
    }
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        cin >> lim;
        explored = 0;
        found = false;
        a.clear();
        bt(0, 1, 41);
        cout << "Case #" << (cn + 1) << ": ";
        if(!found){
            cout << "-1\n";
        }
        else{
            cout << sz(a) << " ";
            for(int i : a) cout << i << " ";
            cout << "\n";
        }
    }
    
    return 0;
}
