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
        // check abs(max, min) == 0
        // max - min cant be 1
        int n; cin >> n;
        vl a(n);
        ll mn = LLONG_MAX, mx = LLONG_MIN;
        multiset<ll> pos, neg;
        vl posv, negv;
        vl ans;
        rep(i, 0, n){
            cin >> a[i];
            if(a[i] == 0){
                ans.pb(a[i]);
            }
            else if(a[i] > 0){
                pos.insert(a[i]);
                posv.pb(a[i]);
            }
            else{
                neg.insert(-a[i]);
                negv.pb(a[i]);
            }
            mn = min(a[i], mn);
            mx = max(a[i], mx);
        }
        sort(all(negv));
        sort(all(posv));
        reverse(all(negv));
        ll diffmax = mx - mn - 1;
        ll minpref = 0, maxpref = 0;
        if(diffmax < 0 || mx == mn){
            cout << "NO" << nL;
            continue;
        }
        ll cursum = 0;
        // while(!pos.empty() && !neg.empty()){
        //     if(pos.empty()){

        //     }
        //     else if(neg.empty();
        // }
        bool negbigger = abs(mn) > mx;
        while(negv.size() > 0 || posv.size() > 0){
            if(negv.size() == 0){
                ans.pb(posv.back());
                cursum += posv.back();
                posv.pop_back();
                
            }
            else if(posv.size() == 0){
                ans.pb(negv.back());
                cursum += negv.back();
                negv.pop_back();
            }
            else{
                if(negbigger){
                    if(negv.back() + cursum < mn){
                        ans.pb(posv.back());
                        cursum += posv.back();
                        posv.pop_back();
                    }
                    else{
                        ans.pb(negv.back());
                        cursum += negv.back();
                        negv.pop_back();
                    }
                }
                else{
                    if(posv.back() + cursum > mx){
                        ans.pb(negv.back());
                        cursum += negv.back();
                        negv.pop_back();
                    }
                    else{
                        ans.pb(posv.back());
                        cursum += posv.back();
                        posv.pop_back();
                    }
                }
            }
        }
        cout << "YES" << nL;
        rep(i, 0, sz(ans)){
            cout << ans[i] << " ";
        }
        cout << nL;
    }
    
    return 0;
}
