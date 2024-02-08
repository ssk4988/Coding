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

vi Z(const string& S, int start) {
	vi z(sz(S));
	int l = -1, r = -1;
	rep(i,1,sz(S)) {
		z[i] = i >= r ? 0 : min(r - i, z[i - l]);
		while (i + z[i] < sz(S) && S[i + z[i]] == S[z[i]])
			z[i]++;
		if (i + z[i] > r)
			l = i, r = i + z[i];
	}
	return z;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    string str; int d; cin >> str >> d;
    int n = sz(str);
    vi z(n + d);
    int l = -1, r = -1;
    int start = 0, ans = 0;
    while(start < n){
        rep(i, start + 1, start + d + 1){
            z[i] = i >= r ? 0 : min(r - i, z[i - l + start]);
            while (i + z[i] < n && str[i + z[i]] == str[z[i] + start])
                z[i]++;
            if (i + z[i] > r)
                l = i, r = i + z[i];
        }
        ans++;
        // cout << "covered " << start << " to " << r << "\n";
        start = r;
        // start++;
    }
    // rep(i, 0, sz(z)){
    //     cout << i << " " << z[i] << "\n";
    // }
    cout << ans << "\n";
    
    return 0;
}
