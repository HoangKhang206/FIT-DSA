#include <iostream>
using namespace std;
//Factorial of a Number
int fatorial(int n) {
    if(n<=1) return 1;
    return n*fatorial(n-1);
}
int main()
{
    int n;
    cout<<"Enter a number: ";
    cin>>n;
    cout << fatorial(n) << endl;
}
