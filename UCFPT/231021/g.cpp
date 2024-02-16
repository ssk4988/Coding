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

string stripspace(string &s){
    string res;
    for(char c : s){
        if(c == ' ') continue;
        res.pb(c);
    }
    return res;
}


bool issectionend(string &s){
    return sz(s) == 80 && s[0] == '=' && s[79] == '=';
}

void printsectionend(){
    rep(i, 0, 80) cout << '=';
    cout << nL;
}

bool isdivider(string &s){
    return sz(s) == 75 && s[0] == '-' && s[74] == '-';
}

void printdivider(){
    rep(i, 0, 75) cout << '-';
    cout << nL;
}

void printheader(){
    string res;
    for(char c : string("Test")) res.pb(c);
    while(sz(res) < 26) res.pb(' ');
    for(char c : string("Result")) res.pb(c);
    while(sz(res) < 34) res.pb(' ');
    for(char c : string("Unit")) res.pb(c);
    while(sz(res) < 50) res.pb(' ');
    for(char c : string("Flag")) res.pb(c);
    while(sz(res) < 75) res.pb(' ');
    cout << res << nL;
}

void printrow(string &field, string &resul, string &unit, string &label){
    string res;
    for(char c : field) res.pb(c);
    while(sz(res) < 26) res.pb(' ');
    for(char c : resul) res.pb(c);
    while(sz(res) < 34) res.pb(' ');
    for(char c : unit) res.pb(c);
    while(sz(res) < 50) res.pb(' ');
    if(label != "Normal") for(char c : label) res.pb(c);
    while(sz(res) < 75) res.pb(' ');
    cout << res << nL;
}

const ll inf = 1e16;
ll getnum(string s){
    ld v = stold(s) * 10'000'000;
    return roundl(v);
}
map<string, vector<pair<pl, string>>> table;
map<string, string> units;

pl getrange(string s){
    s = stripspace(s);
    if(s[0] == '<' && s[1] == '=') return {-inf, getnum(s.substr(2))};
    if(s[0] == '<') return {-inf, getnum(s.substr(1)) - 1};
    if(s[0] == '>' && s[1] == '=') return {getnum(s.substr(2)), inf};
    if(s[0] == '>') return {getnum(s.substr(1)) + 1, inf};
    pl res;
    if(s.find('~') < s.size()){
        int idx = s.find('~');
        res.f = getnum(s.substr(0, idx));
        res.s = getnum(s.substr(idx + 1));
        return res;
    }
    int idx = s.find(',');
    res.f = getnum(s.substr(1, idx));
    res.s = getnum(s.substr(idx + 1, sz(s) - 1 - (idx + 1)));
    if(s[0] == '(') res.f++;
    if(s.back() == ')') res.s--;
    return res;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    // cin.exceptions(cin.failbit);
    string line;
    bool readingref = true;
    while(getline(cin, line)){
        if(readingref){
            string name = line;
            string unit; getline(cin, unit);
            units[name] = unit;
            vector<string> lines;
            getline(cin, line);
            while(!isdivider(line) && !issectionend(line)){
                lines.pb(line);
                getline(cin, line);
            }
            if(sz(lines) == 1){
                pl rng = getrange(lines[0]);
                table[name].push_back({rng, "Normal"});
                table[name].push_back({{-inf, rng.f - 1}, "Abnormal"});
                table[name].push_back({{rng.s + 1, inf}, "Abnormal"});
            }
            else{
                for(int i = 0; i < sz(lines); i += 2){
                    pl rng = getrange(lines[i]);
                    string label = lines[i + 1].substr(2);
                    table[name].push_back({rng, label});
                }
            }
            if(issectionend(line)){
                readingref = false;
            }
            continue;
        }
        string name = line;
        cout << name << nL;
        printdivider();
        printheader();
        printdivider();

        getline(cin, line);
        while(!issectionend(line)){
            string label;
            while(!table.count(label) && sz(label) < sz(line)){
                label.pb(line[sz(label)]);
            }
            while(!table.count(label)){}
            line = line.substr(sz(label));
            line = stripspace(line);
            ll v = getnum(line);
            string category;
            for(auto [rng, diagnosis] : table[label]){
                if(rng.f <= v && v <= rng.s){
                    category = diagnosis;
                    break;
                }
            }
            printrow(label, line, units[label], category);
            getline(cin, line);
        }
        printdivider();
        printsectionend();
    }
    // for(auto [key, val] : table){
    //     cout << "Key: " << key << nL;
    //     for(auto [rng, label] : val){
    //         cout << rng.f << " " << rng.s << " " << label << nL;
    //     }
    // }
    return 0;
}
