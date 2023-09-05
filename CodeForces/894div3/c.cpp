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
        int n; cin >> n;
        vi a(n);
        bool valid = true;
        rep(i, 0, n){
            cin >> a[i];
            if(a[i] > n) valid = false;
        }
        if(!valid){
            cout << "NO\n";
            continue;
        }
        vi a1;
        int idx = n - 1;
        int pre = 0;
        while(idx >= 0){
            int i1 = idx;
            while(a[i1] == a[idx]) i1--;
            rep(j, 0, a[idx] - pre)
                a1.pb(idx + 1);
            pre = a[idx];
            idx = i1;
        }
        if(a1 == a) cout <<"YES\n";
        else cout <<"NO\n";
        // int l = 0, r = n - 1;
        // bool works = true;
        // while(works && l <= r){
        //     int l1 = l, r1 = r;
        //     while(l1 < n && a[l1] == a[l]) l1++;
        //     while(r1 >= 0 && a[r1] == a[r]) r1--;
        //     int lheight = a[l], lwidth = l1 - l;
        //     int rheight = a[r], rwidth = r - r1;
        //     if(r + 1 != lheight){
        //         works = false;
        //         break;
        //     }
        //     if(l + 1 != rheight) works = false;
        //     if(l1 > 0 && a[l1 - 1] -  a[l1] != rwidth){
        //         works = false;
        //         break;
        //     }
        //     if(r1 + 1 < n && a[r1] - a[r1 + 1] != lwidth) works = false;
        //     l = l1, r = r1;
        // }
        // cout << (works ? "YES" : "NO") << nL;
    }
    
    return 0;
}
