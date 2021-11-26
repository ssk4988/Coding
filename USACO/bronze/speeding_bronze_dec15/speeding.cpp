#include <bits/stdc++.h>
using namespace std;

int main()
{
    while (true)
    {
        string s;
        cin >> s;
        if (s == "0")
            break;
        while (s != "0")
        {
            cout << s << " ";
            int n = 1;
            for (int i = 0; i < s.length(); i++)
                n *= (s[i] - '0');
            if (s == to_string(n))
                break;
            ;
            s = to_string(n);
        }
        if (s == "0")
            cout << "0" << endl;
        else
            cout << endl;
    }
    return 0;
}