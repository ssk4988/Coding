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
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int a, b, c, t; cin >> a >> b >> c >> t;
        vi target(1000000, -1);
        target[0] = 0;
        queue<int> q;
        q.push(0);
        while(!q.empty()){
            int v = q.front(); q.pop();
            int va = (v + a) % 1000000;
            int vb = (v * b) % 1000000;
            int vc = (v / c) % 1000000;
            if(target[va] == -1){
                target[va] = target[v] + 1;
                q.push(va);
            }
            if(target[vb] == -1){
                target[vb] = target[v] + 1;
                q.push(vb);
            }
            if(target[vc] == -1){
                target[vc] = target[v] + 1;
                q.push(vc);
            }
        }
        cout << target[t] << "\n";
    }
    
    return 0;
}
