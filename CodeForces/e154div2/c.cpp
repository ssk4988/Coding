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

struct Node{
    vi val;
    vector<Node*> c;
    Node *par = NULL;
    int furthestone = -1;
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        string str; cin >> str;
        int q = sz(str);
        int curlen = 0;
        int maxsort = 0;
        Node *cur = new Node();
        Node *root = cur;
        rep(i, 0, q){
            if(str[i] == '+'){
                Node *nex = new Node();
                nex->par = cur;
                cur->c.pb(nex);
                cur = nex;
            }
            else if(str[i] == '-'){
                cur = cur->par;
            }
            else{
                int v = str[i] - '0';
                cur->val.pb(v);
            }
        }
        bool works = true;
        auto dfs = [&](Node *cur, int d, auto &&dfs)->void{
            for(int i : cur->val){
                if(i == 1){
                    cur->furthestone = max(d, cur->furthestone);
                }
                
            }
            for(Node *nex : cur->c){
                // nex->furthestone = cur->furthestone;
                dfs(nex, d + 1, dfs);
                cur->furthestone = max(cur->furthestone, nex->furthestone);
            }
            for(int i : cur->val){
                if(i == 0){
                    if(d < 2 || cur->furthestone >= d) works = false;
                }
            }
        };
        dfs(root, 0, dfs);
        cout << (works ? "YES" : "NO") << nL;
    }
    
    return 0;
}