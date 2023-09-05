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
    vi ans;
    int nex = 1;
    stack<int> s1, s2;
    s1.push(1e6);
    s2.push(1e6 + 1);
    vi out;
    bool possible = true;
    rep(i, 0, n){
        int a; cin >> a;
        // if(a == nex){
        //     s1.push(a);
        //     continue;
        // }
        stack<int> *mn = &(s1.top() < s2.top() ? s1 : s2);
        stack<int> *mx = &(s1.top() < s2.top() ? s2 : s1);
        if(mn->top() > a){
            mn->push(a);
            ans.pb(mn == &s1 ? 1 : 2);
        }
        else if(mx->top() > a){
            mx->push(a);
            ans.pb(mx == &s1 ? 1 : 2);
        }
        else{
            possible = false;
            break;
        }
        for(;s1.top() == nex || s2.top() == nex; nex++){
            if(s1.top() == nex){
                // ans.pb(1);
                out.pb(s1.top());
                s1.pop();
            }
            else{
                // ans.pb(2);
                out.pb(s2.top());
                s2.pop();
            }
        }
    }
    if(possible){
        for(int i : ans) cout << i << " ";
        cout << nL;
    }
    else cout << "IMPOSSIBLE\n";
    
    return 0;
}
