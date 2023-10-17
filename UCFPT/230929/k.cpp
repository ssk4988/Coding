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

string parsespace(string str){
    string res;res.pb('(');
    for(char c : str){
        if(c == ' ') continue;
        res.pb(c);
    }
    res.pb(')');
    return res;
}
struct Node{
    int v;
    vector<Node*> c;
    Node(int v):v(v){}
};
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    string tree1, tree2; getline(cin, tree1); getline(cin, tree2);
    tree1 = parsespace(tree1), tree2 = parsespace(tree2);
    int idx = 0;
    auto build = [&](string &str, auto &&build)->Node * {
        idx++; // skip (
        int v = 0;
        for(; idx < sz(str) && str[idx] != '(' && str[idx] != ')'; v = v * 10 + str[idx++] - '0');
        Node *cur = new Node(v);
        while(str[idx] != ')'){
            cur->c.pb(build(str, build));
        }
        idx++; // skip )
        sort(all(cur->c), [](Node *a, Node*b)->bool {return a->v < b->v; });
        return cur;
    };
    Node *t1 = build(tree1, build); idx = 0;
    Node *t2 = build(tree2, build);
    auto eq = [](Node *n1, Node *n2, auto &&eq)->bool {
        if(n1->v != n2->v || sz(n1->c) != sz(n2->c)) return false;
        rep(i, 0, sz(n1->c)){
            if(!eq(n1->c[i], n2->c[i], eq)) return false;
        }
        return true;
    };
    cout << (eq(t1, t2, eq) ? "Yes" : "No") << nL;


    
    return 0;
}
