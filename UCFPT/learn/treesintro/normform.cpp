#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vii = vector<pii>;
using vll = vector<pll>;;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

int mxdepth = 0;

struct Node
{
    int b;
    vector<Node*> children;
    int depth = 0;
    Node(int b, int depth = 0) : b(b), depth(depth) {}
    void calc()
    {
        if(sz(children) == 0) return;
        if((depth & 1) == (mxdepth & 1)) {
            b = 0;
            for(auto x : children){
                x->calc();
                if(x->b) b = 1;
            }
        } else {
            b = 1;
            for(auto x : children){
                x->calc();
                if(!x->b) b = 0;
            }
        }
    }
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    // cin.exceptions(cin.failbit);
    string s;
    int cn = 0;
    while(true){
        cin >> s;
        if(s == "()") break;
        int idx = 0;
        auto solve = [&](int depth, auto &&solve) -> Node* {
            mxdepth = max(mxdepth, depth);
            if(s[idx] == 'T' || s[idx] == 'F') {
                return new Node(s[idx++] == 'T', depth);
            }
            Node *cur = new Node('X', depth);
            idx++;
            while(s[idx] != ')'){
                cur->children.push_back(solve(depth + 1, solve));
            }
            idx++;
            return cur;
        };
        mxdepth = 0;
        Node *root = solve(0, solve);
        root->calc();
        int ans = root->b;
        cout << (cn + 1) << ". " << (ans ? "true" : "false") << "\n";
        cn++; 
    }
    
    return 0;
}
