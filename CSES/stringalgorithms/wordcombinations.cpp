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

typedef struct node {
    char cur = '_';
    struct node *next[26];
    bool leaf = false;
    node(){
        rep(i, 0, 26){
            next[i] = NULL;
        }
    }
} node;

ll m = 1000000007;
ll mod(ll k){
    return (k % m + m) % m;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    string str;
    cin >> str;
    int n;
    cin >> n;
    node root;
    node *cur;
    rep(i, 0, n){
        string w; cin >> w;
        cur = &root;
        rep(i, 0, w.length()){
            if(cur->next[w[i] - 'a'] == NULL){
                cur->next[w[i] - 'a'] = new node();
            }
            cur = cur->next[w[i] - 'a'];
        }
        cur->leaf = true;
    }
    cur = &root;
    ll dp[str.length() + 1] = {};
    bool reach[str.length() + 1];
    memset(reach, false, sizeof reach);
    dp[0] = 1;
    reach[0] = true;
    rep(i, 0, str.length() + 1){
        if(!reach[i]) continue;
        cur = &root;
        rep(j, i + 1, str.length() + 1){
            if(cur->next[str[j - 1] - 'a'] == NULL) break;
            cur = cur->next[str[j - 1] - 'a'];
            if(cur->leaf) {
                dp[j] = mod(dp[j] + dp[i]);
                reach[j] = true;
            }
        }
    }
    cout << dp[str.length()] << nL;

    
    return 0;
}