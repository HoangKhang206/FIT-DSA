#include <iostream>
using namespace std;
//Generate All Binary Strings
void generateBinarystrings(int n, string str) {
    if(n==0) {
        cout<<str<<endl;
        return;
    }
    generateBinarystrings(n-1, str+'0');
    generateBinarystrings(n-1, str+'1');
}
int main()
{
    int n;
    cout<<"Enter the number of digits: ";
    cin>>n;
    generateBinarystrings(n, "");
}
