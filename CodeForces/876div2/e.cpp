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
    vi a(n);
    int sum = 0;
    rep(i, 0, n){
        cin >> a[i];
        sum += a[i];
    }
    vvi dp(n + 1, vi(sum + 1));
    dp[0][0] = true;
    rep(i, 0, n){
        rep(j, 0, sum + 1){
            if(!dp[i][j]) continue;
            dp[i + 1][j + a[i]] |= dp[i][j];
            dp[i + 1][j] |= dp[i][j];
        }
    }
    bool firstwin = (sum % 2 == 1) || !dp[n][sum / 2];
    if(firstwin){
        cout << "First" << endl;
        while(true){
            int rem = -1;
            rep(i, 0, n){
                if(a[i] > 0){
                    cout << (i + 1) << endl;
                    rem = i;
                    break;
                }
            }
            assert(rem != -1);
            int rem1 = rem;
            cin >> rem;
            if(rem == 0) return 0;
            if(rem == -1) return 0;
            rem--;
            int m = min(a[rem], a[rem1]);
            sum -= 2 * m;
            a[rem] -= m;
            a[rem1] -= m;
        }
    }
    else{
        vi s1, s2;
        vi ins1(n), ins2(n);
        int sum2 = sum / 2, idx = n;
        while(idx > 0){
            bool belongs1 = false;
            bool cs1 = dp[idx - 1][sum2 - a[idx - 1]], cs2 = dp[idx - 1][sum2];
            if(cs1 && cs2){
                if(sz(s1) == 0) belongs1 = true;
            }
            else if(cs1){
                belongs1 = true;
            }
            else belongs1 = false;
            if(belongs1){
                s1.pb(idx - 1);
                ins1[idx - 1] = true;
                sum2 -= a[idx - 1];
            }
            else{
                s2.pb(idx - 1);
                ins2[idx - 1] = true;
            }
            idx--;
        }
        assert(sum2 == 0);
        cout << "Second" << endl;
        while(true){
            int rem; cin >> rem;
            if(rem == 0 || rem == -1) return 0;
            rem--;
            int rem1 = -1;
            if(ins1[rem]){
                for(int i : s2){
                    if(a[i] > 0){
                        rem1 = i;
                        break;
                    }
                }
            }
            else{
                for(int i : s1){
                    if(a[i] > 0){
                        rem1 = i;
                        break;
                    }
                }
            }
            assert(rem1 != -1);
            int m = min(a[rem1], a[rem]);
            sum -= 2 * m;
            a[rem] -= m;
            a[rem1] -= m;
            cout << (rem1 + 1) << endl;
        }
    }
    
    
    return 0;
}
