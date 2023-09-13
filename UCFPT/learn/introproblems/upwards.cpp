#include <bits/stdc++.h>
using namespace std;

int main(){
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    for(int i = 0; i < n; i++){
        string str; cin >> str;
        string str1(str);
        sort(str1.begin(), str1.end());
        bool works = true;
        for(int j = 1; j < str1.size(); j++){
            if(str1[j] == str1[j - 1]) works = false;
        }
        if(str == str1 && works) cout << "YES\n";
        else cout << "NO\n";
    }
}
