#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i, a, b) for (int i = a; i < (b); i++)
#define pb push_back
#define f first
#define s second

using vi = vector<int>;
using ll = long long;
using pi = pair<int, int>;

struct Node{
    vector<Node*> nex;
    Node() : nex(26, NULL){}
};

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int q; cin >> q;
    bool rev = false;
    Node *root = new Node(), *rroot = new Node();
    auto trav = [](Node *cur, string str)->bool{
        rep(i, 0, sz(str)){
            if(cur->nex[str[i] - 'a']) cur = cur->nex[str[i] - 'a'];
            else return false;
        }
        return true;
    };
    auto add = [](Node *cur, string str)->void{
        rep(i, 0, sz(str)){
            if(!cur->nex[str[i] - 'a']) cur->nex[str[i] - 'a'] = new Node();
            cur = cur->nex[str[i] - 'a'];
        }
    };
    rep(i, 0, q){
        int t; cin >> t;
        if(t == 1){
            string str; cin >> str;
            add(rev ? rroot : root, str);
            reverse(all(str));
            add(rev ? root : rroot, str);
        }
        if(t == 2){
            string str; cin >> str;
            bool h = trav(rev ? rroot : root, str);
            cout << h << "\n";
        }
        if(t == 3) {
            rev = !rev;
        }
    }
}
