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

struct DSU
{
    vi parent;
    vi siz;
    DSU(int n) : parent(n), siz(n, 1)
    {
        rep(i, 0, n)
        {
            parent[i] = i;
        }
    }
    int find(int a)
    {
        if (parent[a] == a)
        {
            return a;
        }
        return parent[a] = find(parent[a]);
    }

    void join(int a, int b)
    {
        a = find(a);
        b = find(b);
        if (a == b)
            return;
        if (siz[a] < siz[b])
        {
            swap(a, b);
        }
        parent[b] = a;
        siz[a] += siz[b];
    }

    int get_siz(int a)
    {
        return siz[find(a)];
    }
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m;
    cin >> n >> m;
    DSU d(n);
    rep(i, 0, m){
        int a, b; cin >> a >> b;
        a--,b--;
        d.join(a, b);
    }
    vi sizes;
    rep(i, 0, n){
        if(d.find(i) == i){
            sizes.pb(d.get_siz(i));
        }
    }
    bitset<100001> bs;
    bs[0] = 1;
    rep(i, 0, sz(sizes)){
        bs |= bs << sizes[i];
    }
    rep(i, 1, n + 1){
        cout << bs[i];
    }
    cout << nL;
    return 0;
}
