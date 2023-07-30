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

struct Node{
    Node *left = 0, *right = 0;
    int val;
    Node(int v) : val(v){};
    void postorder(){
        if(left) left->postorder();
        if(right) right->postorder();
        cout << val << " ";
    }
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vi preorder(n), inorder(n), rev(n + 1);
    rep(i, 0, n) cin >> preorder[i];
    rep(i, 0, n){
        cin >> inorder[i];
        rev[inorder[i]] = i;
    }
    int idx = 0;
    auto construct = [&](int left, int right, auto &&construct)->Node*{
        if(idx >= n || left > right) return NULL;
        Node *root = new Node(preorder[idx++]);
        int split = rev[root->val];
        root->left = construct(left, split - 1, construct);
        root->right = construct(split + 1, right, construct);
        return root;
    };
    Node *tree = construct(0, n - 1, construct);
    tree->postorder();
    cout << nL;
    
    return 0;
}