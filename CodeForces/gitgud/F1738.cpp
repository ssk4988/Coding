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

struct UF {
    vi e;
    UF(int n) : e(n, -1) {}
    int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
    bool join(int a, int b) {
        a = find(a), b = find(b);
        if(a == b) return false;
        if(e[a] > e[b]) swap(a, b);
        e[a] += e[b]; e[b] = a;
        return true;
    }
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n; cin >> n;
        vi d(n);
        vi used(n);
        UF uf(n);
        priority_queue<pi> pq;
        rep(i, 0, n){
            cin >> d[i];
            pq.push({d[i], i});
        }
        int cur = 0;
        while(!pq.empty()){
            auto [deg, u] = pq.top(); pq.pop();
            if(used[u]) continue;
            used[u] = true;
            rep(i, 0, deg){
                cout << "? " << (u+1) << endl;
                int res; cin >> res; res--;
                uf.join(res, u);
                if(used[res]) break;
                used[res] = true;
            }
        }
        cout << "! ";
        rep(i, 0, n){
            cout << uf.find(i) +1 << " ";
        }
        cout << endl;
    }
    
    return 0;
}
