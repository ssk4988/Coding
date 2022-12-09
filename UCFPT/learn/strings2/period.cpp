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

vector<int> prefix_function(string str) {
    int n = (int)str.length();
    vector<int> pi(n);
    for (int i = 1; i < n; i++) {
        int j = pi[i-1];
        while (j > 0 && str[i] != str[j])
            j = pi[j-1];
        if (str[i] == str[j])
            j++;
        pi[i] = j;
    }
    return pi;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n;
    cin >> n;
    int nc = 1;
    while(n > 0){
        string str; cin >> str;
        vi pi = prefix_function(str);
        cout << "Test case #" << nc << nL;
        rep(i, 2, n + 1){
            if(pi[i - 1] > 0 && i % (i - pi[i - 1]) == 0){
                cout << i << " " << (i / (i - pi[i - 1])) << nL;
            }
        }
        cout << nL;
        nc++;
        cin >> n;
    }
    
    return 0;
}