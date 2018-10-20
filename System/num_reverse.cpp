/*************************************************************************
    > File Name:    num_reverse.cpp
    > Author:       Hunter
    > Mail:         hunter.520@qq.com
    > Created Time: Sat 20 Oct 2018 12:37:54 PM PDT
        system("pause");
 ************************************************************************/
 

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
int main() {
        string s;
        cin >> s;
        string::iterator it = s.end();
        while(*(it-1)=='0' && (it-1) != s.begin()) it--;
        *it = '\0';
        s[0] == '-' ? reverse(s.begin()+1, it) : reverse(s.begin(), it);
        cout << s;
        return 0;
}

