#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int long long
struct st { int len, pos, term; st *link; map<char,st*> next; ll ocur = -1; bool seen = false; ll paths = -1;};
st *suffixAutomaton(string &str) {
    st *last = new st(), *root = last;
    for (auto c : str) {
        st *p = last, *cur = last = new st {last->len + 1, last->len};
        while (p && !p->next.count(c))
            p->next[c] = cur, p = p->link;
        if (!p) cur ->link = root;
        else { 
            st *q = p->next[c];
            if (p->len + 1 == q->len) cur->link = q;
            else {
                st *clone = new st{p->len + 1, q->pos, 0, q->link, q->next};
                for (; p && p->next[c] == q; p = p->link)
                    p->next[c] = clone;
                q->link = cur->link = clone;
            }
        }
    }
    while(last) last->term = 1, last = last->link;
    return root;
}

ll oc(st *node){
    if(node->ocur != -1) return node->ocur;
    node->ocur = node->term;
    for(auto [ch,nxt]: node->next){
        node->ocur+=oc(nxt);
    }
    return node->ocur;
}
array<ll,10> digits;

void addDigits(int x, ll g){
    //cout << g << " " << "strings" << "ocur " << x << "\n";
    while(x){
        digits[x%10]+=g;
        x/=10;
    }
    return;
}

vector<st* > listofNodes;
void dfs(st *node){
    if(node->seen) return;
    listofNodes.push_back(node);
    node->seen = true;
    int guys = node->len;
    st *sli = node->link;
    if(sli) guys-=sli->len;
    int occur = oc(node);
    addDigits(occur,guys);
    for(auto[ch,nxt]: node->next){
        dfs(nxt);
    }
}

ll pathsFrom(st *node){
    if(node->paths != -1) return node->paths;
    node->paths = 1;
    for(auto [ch,nxt]: node->next){
        node->paths+=pathsFrom(nxt);
    }
    return node->paths;
}

ll getLetter(st *node, char ch){
    if(node->ocur != -1) return node->ocur;
    ll ans = 0;
    for(auto [nxtCH,nxt]: node->next){
        ans+=getLetter(nxt,ch);
        if(nxtCH==ch) ans+= pathsFrom(nxt);
    }
    node->ocur = ans;
    return node->ocur;
}

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    for(int i = 0; i < 10; i++) digits[i] = 0;
    string s; cin >> s;
    set<char> letters;
    map<char,ll> ans;
    for(auto ch: s) letters.insert(ch);
    st *sam = suffixAutomaton(s);
    dfs(sam);
   // for(auto el: digits) cout << el << " "; cout << "\n";
    vector<pair<char,ll>> answer;
    for(int i = 0; i < digits.size(); i++){
        if(digits[i]){
            answer.push_back({i+'0',digits[i]});
        }
    }

    for(auto ch: letters){
        for(int i = 0; i < listofNodes.size(); i++){
            listofNodes[i]->paths = -1;
            listofNodes[i]->seen = false;
            listofNodes[i]->ocur = -1;
        }
        ll cnt = getLetter(sam,ch);
        if(cnt){
            answer.push_back({ch,cnt});
        }
       // cout << ch << " " << cnt << "\n";
    }

    sort(answer.begin(),answer.end());
    for(auto [ch,cnt]: answer){
        cout << ch << " " << cnt << "\n";
    }






    return 0;
}