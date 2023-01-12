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

void update(vi &segtree, int idx, int val)
{
    int segsz = sz(segtree) / 2;
    idx += segsz;
    segtree[idx] = val;
    for (; idx > 1; idx >>= 1)
    {
        segtree[idx >> 1] = max(segtree[idx], segtree[idx ^ 1]);
    }
}

int maxquery(vi &segtree, int l, int r)
{
    int segsz = sz(segtree) / 2;
    int res = 0;
    for (l += segsz, r += segsz + 1; l < r; l >>= 1, r >>= 1)
    {
        if (l & 1)
            res = max(res, segtree[l++]);
        if (r & 1)
            res = max(res, segtree[--r]);
    }
    return res;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n; cin >> n;
        vi a(n), b(n);
        int siz = 1;
        while(siz < n) siz *= 2;
        vi seg(2 * siz, INT_MIN);
        map<int, set<int>> ind;
        bool works = true;
        rep(i, 0, n){
            cin >> a[i];
        }
        rep(i, 0, n){
            cin >> b[i];
            
            update(seg, i, b[i]);
            if(a[i] != b[i]) ind[b[i]].insert(i);
            if(a[i] < b[i]) works = false;
        }
        int r; cin >> r;
        vi c(r);
        rep(i, 0, r){
            cin >> c[i];
        }
        sort(all(c));
        
        for(int i = r - 1; i >= 0 && works; i--){
            if(ind[c[i]].size() <= 0) continue;
            int fir = *(ind[c[i]].begin());
            while(ind[c[i]].size() && works){
                int l = *(ind[c[i]].begin());
                int k = maxquery(seg, fir, l);
                if(k > c[i]){
                    break;
                }
                else{
                    a[l] = min(a[l], c[i]);
                    update(seg, *(ind[c[i]].begin()), c[i]);
                    ind[c[i]].erase(ind[c[i]].begin());
                }
            }
        }
        rep(i, 0, n){
            if(a[i] != b[i]) works = false;
        }
        cout << (works ? "YES" : "NO") << "\n";
    }

    
    return 0;
}