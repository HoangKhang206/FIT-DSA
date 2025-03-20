#include <iostream>
using namespace std;
//Fibonacci Series
int Fibonaccy(int n) {
    if(n==0) return 0;
    if(n==1) return 1;
    return Fibonaccy(n-1) + Fibonaccy(n-2);
}
int main()
{
    int n;
    cout <<"Enter a number: ";
    cin>>n;
    for(int i=1;i<=n;i++) {
        cout<<Fibonaccy(i)<<"\t";
    }
}
