#include <bits/stdc++.h>
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
    string str; cin >> str;
    int n= sz(str);
    vi freq(26);
    rep(i, 0, n) freq[str[i] - 'A']++;
    auto getmax = [&]()->int{
        int mx = 0;
        for(int i : freq) mx = max(mx, i);
        return mx;
    };
    int v = getmax();
    int left = n;
    if(v > (left + 1) / 2){
        cout << "-1\n";
        return 0;
    }
    int pre = -1;
    rep(i, 0, n){
        rep(j, 0, 26){
            if(j == pre || freq[j] == 0) continue;
            freq[j]--;
            if(getmax() <= left / 2){
                cout << char('A' + j);
                left--;
                pre = j;
                break;
            }
            freq[j]++;
        }
    }
    cout << nL;
    
    return 0;
}
