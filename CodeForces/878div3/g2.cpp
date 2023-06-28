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
    int x; cin >> x;
    srand(time(NULL));
    auto query = [&](int k)->int{
        cout << "+ " << k << nL;
        cout.flush();
        int v; cin >> v;
        return v;
    };
    int maxn = 1e6;
    int mx = 0;
    ll delta = 0;
    int k = 340;
    rep(i, 0, k){
        ll v = (rand() % maxn) + 1;
        delta += v;
        mx = max(mx, query(v));
    }
    cout << "- " << delta << endl;
    cout.flush();
    int x1; cin >> x1;
    assert(x == x1);
    int x2 = query(mx);
    delta = mx;
    int d = (1000-3-k)/2;
    unordered_map<int, int> p;
    p[x] = mx;
    int jumpsize = d;
    int curplace = 0;
    rep(i, 1, jumpsize){
        int v = query(1);
        curplace += 1;
        delta++;
        if(v == x){
            cout << "! " << delta << nL;
            return 0;
        }
        // if(p.count(v)){
        //     cout << "! " << (i - p[v]) << nL;
        //     return 0;
        // }
        p[v] = i;
    }
    cout << "- " << delta << endl;
    cout.flush();
    delta = 0;
    while(true){
        cout << "- " << jumpsize << endl;
        cout.flush();
        int v; cin >> v;
        delta += jumpsize;
        if(p.count(v)){
            cout << "! " << (p[v] + delta) << nL;
            return 0;
        }
    }

    
    return 0;
}
