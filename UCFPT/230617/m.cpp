#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define pb push_back
#define f first 
#define s second
using ll = long long;
using pi = pair<int, int>;
using vi = vector<int>;
using vl = vector<ll>;
using vpi = vector<pi>;

int main() {
    // cin.tie(0)->sync_with_stdio(0);
    // cin.exceptions(cin.failbit);
    unordered_map<string, char> mm;
    mm["q"] = mm["iu"] = 'q';
    mm["w"] = mm["ei"] = 'w';
    mm["e"] = 'e';
    mm["r"] = mm["uan"] = 'r';
    mm["t"] = mm["ue"] = 't';
    mm["y"] = mm["un"] = 'y';
    mm["u"] = mm["sh"] = 'u';
    mm["i"] = mm["ch"] = 'i';
    mm["o"] = mm["uo"] = 'o';
    mm["p"] = mm["ie"] = 'p';
    mm["a"] = 'a';
    mm["s"] = mm["ong"] = mm["iong"] = 's';
    mm["d"] = mm["ai"] = 'd';
    mm["f"] = mm["en"] = 'f';
    mm["g"] = mm["eng"] = 'g';
    mm["h"] = mm["ang"] = 'h';
    mm["j"] = mm["an"] = 'j';
    mm["k"] = mm["uai"] = mm["ing"] = 'k';
    mm["l"] = mm["uang"] = mm["iang"] = 'l';
    mm["z"] = mm["ou"] = 'z';
    mm["x"] = mm["ia"] = mm["ua"] = 'x';
    mm["c"] = mm["ao"] = 'c';
    mm["v"] = mm["zh"] = mm["ui"] = 'v';
    mm["b"] = mm["in"] = 'b';
    mm["n"] = mm["iao"] = 'n';
    mm["m"] = mm["ian"] = 'm';
    int wordcnt = 0;
    string line;
    while(getline(cin,line))
    {
        if (line.empty())
            break;
        istringstream in(line);
        string word;
        while(in >> word){
            wordcnt++;
            if(sz(word) == 1){
                cout << word << word << " ";
            }
            else if(sz(word) == 2){
                cout << word << " ";
            }
            else{
                if(mm.count(word)){
                    cout << mm[word.substr(0, 1)] << mm[word] << " ";
                }
                else{
                    bool found = false;
                    for(int i = sz(word) - 1; i > 0; i--){
                        string w1 = word.substr(0, i);
                        if(mm.count(w1)){
                            cout << mm[w1] << mm[word.substr(i)] << " ";
                            found = true;
                            break;
                        }
                    }
                    assert(found);
                }
            }
        }
        cout << "\n";
    }
}
