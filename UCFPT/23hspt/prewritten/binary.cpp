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
        int n;
        string str;
        cin >> n >> str;
        ll low = 0;
        ll high = (ll)n * n;
        while (low < high)
        {
            ll mid = low + (high - low + 1) / 2;
            ll ans = 0;
            int l = 0, r = 0;
            ll curval = str[0] - '0';
            while (l < n && r < n)
            {
                while(r < l){
                    curval <<= 1;
                    curval |= str[++r] - '0';
                }
                while (curval < mid && r + 1 < n)
                {
                    curval <<= 1;
                    curval |= str[++r] - '0';
                }
                if(curval >= mid){
                    ans += n - r;
                }
                curval -= curval & (1 << (r - l));
                l++;
            }
            if(ans >= mid){
                low = mid;
            }
            else{
                high = mid - 1;
            }
        }
        cout << low << nL;
    }

    return 0;
}