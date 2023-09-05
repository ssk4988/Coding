#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)x.size()


int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    string str1, str2; cin >> str1 >> str2;
    set<char> vowels = {'a', 'e', 'i', 'o', 'u'};
    int idx1 = 1;
    while(idx1 < sz(str1) && vowels.count(str1[idx1]) == 0) idx1++;
    int idx2 = sz(str2) - 2;
    while(idx2 >= 0 && vowels.count(str2[idx2]) == 0) idx2--;
    bool v1 = idx1 < sz(str1), v2 = idx2 >= 0;
    if(v2){
        cout << str1.substr(0, idx1) << "" << str2.substr(idx2) << "\n";
    }
    else if(v1){
        cout << str1.substr(0, idx1 + 1) << "" << str2 << "\n";
    }
    else{
        cout << str1 << "o" << str2 << "\n";
    }

}
