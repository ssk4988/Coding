#include <bits/stdc++.h>
using namespace std;

int main(){
    cin.tie(0)->sync_with_stdio(0);
    int cn = 0;
    while(true){
        string str1, str2; cin >> str1 >> str2;
        if(str1 == "END" && str2 == "END") break;
        vector<int> f1(26), f2(26);
        for(char c : str1) f1[c - 'a']++;
        for(char c : str2) f2[c - 'a']++;
        cout << "Case " << (cn + 1) << ": ";
        if(f1 == f2){
            cout << "same\n";
        }
        else cout << "different\n";
        cn++;
    }
}
