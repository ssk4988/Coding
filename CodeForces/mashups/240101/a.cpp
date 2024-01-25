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

struct UF
{
    map<int, int> p, d; // rep, dist to rep
    bool sameSet(int a, int b) { return find(a) == find(b); }
    int find(int x)
    {
        if(!p.count(x)){
            p[x] = x;
            d[x] = 0;
        }
        if (p[x] == x)
            return x;
        int r = find(p[x]);
        if (r == p[x])
            return r;
        d[x] ^= d[p[x]];
        p[x] = r;
        return r;
        // return e[x] < 0 ? x : e[x] = find(e[x]);
    }
    bool join(int a, int b, int x)
    {
        int ra = find(a), da = d[a], rb = find(b), db = d[b];
        // a = find(a), b = find(b);
        if (ra == rb)
            return false;
        if (ra > rb)
        {
            swap(a, b);
            swap(ra, rb);
            swap(da, db);
        }
        p[rb] = ra;
        d[rb] = da ^ x ^ db;
        return true;
    }
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int q; cin >> q;
    int last = 0;
    UF uf;
    rep(i, 0, q){
        int t; cin >> t;
        if(t == 1){
            int l, r, x; cin >> l >> r >> x;
            l ^= last, r ^= last, x ^= last;
            if(l > r) swap(l, r);
            r++;
            uf.join(l, r, x);
        }
        else{
            int l, r; cin >> l >> r;
            l ^= last, r ^= last;
            if(l > r) swap(l, r);
            r++;
            int ans = -1;
            if(uf.sameSet(l, r)){
                uf.find(l), uf.find(r);
                ans = uf.d[l] ^ uf.d[r];
            }
            cout << ans << nL;
            if(ans == -1) last = 1;
            else last = ans;
        }
    }
    return 0;
}
