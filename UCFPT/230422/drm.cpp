#include <bits/stdc++.h>
using namespace std;

int main(){
    cin.tie(0)->sync_with_stdio();
    cin.exceptions(cin.failbit);
    string str; cin >> str;
    int n = str.length();
    vector<int> a(n);
    for(int i=  0; i< n; i++){
        a[i] = str[i] - 'A';
    }
    int rot1 = 0, rot2 = 0;
    for(int i = 0; i < n; i++){
        if(i < n/2){
            rot1+= a[i];
        }
        else{
            rot2 += a[i];
        }
    }
    for(int i = 0; i < n; i++){
        if(i < n/2){
            a[i] = (a[i] + rot1) % 26;
        }
        else{
            a[i] = (a[i] + rot2) % 26;
        }
    }
    for(int i = 0; i < n/ 2; i++){
        cout << (char)('A' + ((a[i] + a[i + n/2])%26));
    }
    cout << "\n";

    return 0;
}