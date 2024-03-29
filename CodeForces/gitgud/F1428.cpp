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
    int n; cin >> n;
    string str; cin >> str;
    ll tot = 0, cur = 0;
    vl hist(n+5);
    // int iter = 0;
	rep(i, 0, n) {
        // cout << i << endl;
        // iter++;
        // if(iter > n + 10) break;
		if (str[i] == '0') tot += cur;
		else{
			int l = i, r = i;
			while (r < n && str[r] == '1') r++;
            // cout << l << "  " << r << endl;
			for (int x = 1; x <= r-l; ++x){
				cur += (l+x) - hist[x];
				tot += cur;
				hist[x] = r-x+1;
			}
			i = r-1;
		}
	}
	cout << tot << '\n';
    
    return 0;
}
