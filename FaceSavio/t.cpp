#include <iostream>
using namespace std;

int main(){

    string s = "Oi ola SAViO TeLES !@#$_)%&*/";

    int i = 0;
    while(s[i]){
        s[i++] |= 1 << 5;
    }

    cout << s << '\n';

    return 0;
}