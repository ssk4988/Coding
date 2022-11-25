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
    int nc;
    cin >> nc;
    rep(cn, 0, nc)
    {
        vector<ll> left;
        vector<ll> right;
        ll k;
        cin >> k;
        ll diff = k;
        ll gt = 1;
        while (gt <= k)
        {
            gt *= 3;
        }
        while(gt > 0){
            if(abs(diff + gt) <= gt / 2){
                diff += gt;
                left.pb(gt);
            }
            else if(abs(diff - gt) <= gt / 2){
                diff -= gt;
                right.pb(gt);
            }
            gt /= 3;
        }
        sort(all(left));
        sort(all(right));
        cout << "left pan:";
        for(int i = left.size() - 1; i >= 0; i--){
            cout << " " << left[i];
        }
        cout << nL << "right pan:";
        for(int i = right.size() - 1; i >= 0; i--){
            cout << " " << right[i];
        }
        cout << nL;
        if(cn + 1 < nc){
            cout << nL;
        }
    }

    return 0;
}