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
    int t, n; cin >> t >> n;
    const int maxmoves = n;
    vector<vector<bool>> dp(maxmoves + 1, vector<bool>(1 << n));
    dp[0][0] = true;
    int mask1, mask2;
    rep(i, 0, maxmoves){
        rep(j, 0, 1 << n){
            if(!dp[i][j]) continue;
            rep(k, 0, n){
                if(k + i + 1 > n){
                    mask1 = ((1 << (n - k)) - 1) << k;
                    mask2 = (1 << (k + i + 1 - n)) - 1;
                }
                else{
                    mask1 = ((1 << (i + 1)) - 1) << k;
                    mask2 = 0;
                }
                dp[i + 1][j ^ mask1 ^ mask2] = true;
                // assert((j ^ mask1 ^ mask2)< (1 << n));
            }
        }
    }
    rep(i, 0, t){
        string str1, str2; cin >> str1 >> str2;
        reverse(all(str1));
        reverse(all(str2));
        int m1 = stoi(str1, NULL, 2), m2 = stoi(str2, NULL, 2);
        // m1 = ((1 << n) - 1) & ~m1;
        if(m1 == 0){
            cout << "0\n"; continue;
        }
        // cout << "current masks: " << m1 << " " << m2 << nL;
        bool found = false;
        rep(j, 1, maxmoves + 1){
            int m3 = m1;
            int mask1 = 0, mask2 = 0;
            rep(k, 0, n){
                if((m2 & (1 << k)) == 0) continue;
                if(k + j > n){
                    mask1 ^= ((1 << (n - k)) - 1) << k;
                    mask2 ^= (1 << (k + j - n)) - 1;
                }
                else{
                    mask1 ^= ((1 << (j)) - 1) << k;
                }
            }
            m3 ^= mask1 ^ mask2;
            // cout << "rotate by " << j << " and got " << m3 << " with masks " << mask1 << " " << mask2 << nL;
            if(dp[j][m3]){
                cout << j << nL;
                found = true;
                break;
            }
        }
        assert(found);
        // cout << m1 << " " << m2 << nL;
    }
    
    return 0;
}
